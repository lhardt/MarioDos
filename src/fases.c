#ifndef FASES_C
#define FASES_C

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "jogo.h"
#include "textura.h"
#include "assert.h"

#include "recursos.h"// temporario
#include <unistd.h>

// carrega os conteúdos do arquivo em f
bool load_fases(Fase * f, char * arquivo){
	ASSERT(f != NULL && arquivo != NULL);

	// O endereço é o caminho + nome do arquivo.
	char * tmp = malloc(strlen(CAMINHO_FASES) + strlen(arquivo)+1);
    sprintf(tmp, "%s%s", CAMINHO_FASES, arquivo);
	FILE * entrada = fopen(tmp, "r");
	free(tmp);

	if (entrada == NULL){
		printf ("Arquivo não encontrado.\n");
	}
	// Lê o arquivo
    if(!feof(entrada)){
        for (int i_linha=0; i_linha < FASE_ALTURA; ++i_linha){
			for(int i_char = 0; i_char < FASE_LARGURA; ++i_char ){
				f->mapa[i_linha][i_char] = fgetc(entrada);
			}
        }
		fscanf(entrada, "%d %d %d\n", &f->n_tartarugas, &f->n_caranguejos, &f->delay);

		for(int i_linha = FASE_ALTURA - TILES_CHAO; i_linha < FASE_ALTURA; ++i_linha){
			for(int i_char = 0; i_char < FASE_LARGURA; ++i_char ){
				f->mapa[i_linha][i_char] = 'T';
			}
		}
    }

	// Configura o Mario
	f->mario.vidas = 3;
	f->mario.pos = (Vector2f) {10, 5};
	//f->n_inimigos = f->n_caranguejos +f->n_tartarugas;

	return true;
}

void tile_desenha(int x, int y, Color cor){
	DrawRectangle(x * TILE_LARGURA, y * TILE_ALTURA, TILE_LARGURA, TILE_ALTURA, cor);
}

void desenha_vidas(Jogo * j, int n_vidas){
	ASSERT(n_vidas >= 0 && n_vidas <= 3);
	if(n_vidas == 0) return;

	Vector2 pos = (Vector2) {.x = POS_VIDAS_X, .y = POS_VIDAS_Y};
	for(int i = 0; i < n_vidas; ++i){
		textura_desenha(j, T_CORACAO, pos);
		pos.x += POS_VIDAS_ESPACO;
	}
}

void desenha_pontos(Jogo * j, int n_pontos){
	Vector2 pos = {
		.x = 250,
		.y = 20
	};
	texto_centralizado(j->fonte_menu, "PONTOS:", pos, GREEN);

	pos.x += 120;
	char numstr[30];
	sprintf(numstr, "%d", n_pontos);
	texto_centralizado(j->fonte_menu, numstr, pos, GREEN);
}

void desenha_num_fase(Jogo * j){
	Vector2 pos = { .x = 550, .y = 20 };
	texto_centralizado(j->fonte_menu, "FASE:", pos, GREEN);

	pos.x += 80;
	char numstr[30];
	sprintf(numstr, "%d", j->num_fase);
	texto_centralizado(j->fonte_menu, numstr, pos, GREEN);
}

void desenha_nome_jogador(Jogo * j){
	Vector2 pos = { .x = 850, .y = 20 };
	texto_centralizado(j->fonte_menu, "JOGADOR:", pos, GREEN);

	pos.x += 120;
	texto_centralizado(j->fonte_menu, j->nome_jogador, pos, GREEN);
}

void desenha_cano_s(Jogo * j, int x,int y){
    Vector2f pos_tiles = {.x = 1.0 + x, .y = 1.0 + y};
    Vector2 pos_screen = posfloat_para_tela(pos_tiles);

    if (x > FASE_LARGURA/2){
        textura_desenha(j,D_CANO_S, pos_screen);
    } else{
        textura_desenha(j,E_CANO_S, pos_screen);
    }
}

void desenha_canos_i(Jogo * j){
    Vector2 pos_screen_d = posfloat_para_tela(((Vector2f){.x=1.0+114, .y = 1.0+23}));
    Vector2 pos_screen_e = posfloat_para_tela(((Vector2f){.x=1.0+4.7, .y =1.0+23}));

    textura_desenha(j,D_CANO_I, pos_screen_d);
    textura_desenha(j,E_CANO_I, pos_screen_e);
}

void fases_desenha(Jogo * j){
	// /* Teste: desenha as 4 bordas da tela. */
	// for(int i = 0; i < FASE_ALTURA; ++i){
	// 	tile_desenha(0,i, RED);
	// 	tile_desenha(119,i, RED);
	// }
	// for(int i = 0; i < FASE_LARGURA; ++i){
	// 	tile_desenha(i,0, RED);
	// 	tile_desenha(i,27, RED);
	// }
    Fase *f = &j->tela_jogo->fase;

    for (int y=0; y < FASE_ALTURA; y++){
		for (int x=0; x<FASE_LARGURA; x++){
			switch(f->mapa[y][x]){
			    case 'c':{
					Vector2f pos_tiles = {.x = 1.0 + x, .y = 1.0 + y};
					Vector2 pos_screen = posfloat_para_tela(pos_tiles);
					//se for desenhar na parte direita da tela
					if (x > FASE_LARGURA/2){
						textura_desenha(j,D_CANO_S, pos_screen);
					} else{
						textura_desenha(j,E_CANO_S, pos_screen);
					}
					break;
				}
				case 'b': {
					Vector2f pos_tiles = {.x = x, .y = y};
					Vector2 pos_screen = posfloat_para_tela(pos_tiles);
					textura_desenha(j,T_POW, pos_screen);
					tile_desenha(x,y, PINK);
					break;
				}
				case 'p': {
					tile_desenha(x,y, BLUE);
					break;
				}
				case 'T': {
					tile_desenha(x,y, PINK);
					break;
				}
				case '1':  case '2': case '3':  case '4': case '5':  case '6': case '7':  case '8': case '9': {
                    Vector2f pos_tiles;
                    Vector2 pos_screen;
                    //se for desenhar na parte direita da tela
                    if (x > FASE_LARGURA/2){
                        pos_tiles = (Vector2f) {.x = 1.2 + x, .y = 1.0 + y};
                        pos_screen = posfloat_para_tela(pos_tiles);
                        textura_desenha(j,D_CANO_I, pos_screen);
                    } else{
                        pos_tiles = (Vector2f){.x = x, .y = 1.0 + y};
                        pos_screen = posfloat_para_tela(pos_tiles);
                        textura_desenha(j,E_CANO_I, pos_screen);
                    }
                    break;
				}

			}
			//printf("\nf mapa int? %d", (int) f->mapa[y][x]>=0);
			if((int)f->mapa[y][x]>=0 && (int)f->mapa[y][x]<=9){
                Vector2f pos_tiles = {.x = 1.0 + x, .y = 1.0 + y};
                Vector2 pos_screen = posfloat_para_tela(pos_tiles);
                //se for desenhar na parte direita da tela
                if (x > FASE_LARGURA/2){
                    textura_desenha(j,D_CANO_I, pos_screen);
                } else{
                    textura_desenha(j,E_CANO_I, pos_screen);
                }

			}
	    }
    }

	desenha_vidas(j,  f->mario.vidas);
	desenha_pontos(j, j->pontos);//desenha_pontos(j, f->mario.score);
	desenha_num_fase(j);
	desenha_nome_jogador(j);
	textura_desenha(j, CHAO, (Vector2){.x = 450, .y = 675});
	textura_desenha(j, CHAO, (Vector2){.x = 1345, .y = 675});
	//desenha_cano_s(j,7,5);
	//desenha_cano_s(j,112,5);
	//desenha_canos_i (j);

}

bool fases_inicia(Jogo * j){
	TODO();
    return true;
}

void fases_termina(Jogo * j){
	TODO();
}

bool mario_no_power (Fase * fase){
	Vector2f pos = fase->mario.pos;

	// Margem de 0.1 porque o chão é no próximo tile.
	double y_acima  = pos.y - MARIO_ALTURA/2 - 0.1;
	int x_inicial = (int) (pos.x - MARIO_LARGURA/2 );
	int x_final   = (int) (pos.x + MARIO_LARGURA/2 );

	bool result = false;
	for(int x = x_inicial; x <= x_final && result == false; ++x){
		result |= (fase->mapa[(int)y_acima][x]  == 'b') || (fase->mapa[(int)y_acima][x-1]  == 'b') ||
		(fase->mapa[(int)y_acima][x-2]  == 'b') || (fase->mapa[(int)y_acima][x+1]  == 'b') ;
	}
	return result;
}


bool personagem_no_teto(Fase * fase, Vector2f * pos, float pLargura, float pAltura){
	Vector2f pos_mario = fase->mario.pos;

	// Margem de 0.1 porque o chão é no próximo tile.
	double y_acima  = pos_mario.y - pAltura/2 - 0.1;
	int x_inicial = (int) (pos->x - pLargura/2 );
	int x_final   = (int) (pos->x + pLargura/2 );

	bool result = false;
	for(int x = x_inicial; x <= x_final && result == false; ++x){
		result |= (fase->mapa[(int)y_acima][x]  == 'p') || (fase->mapa[(int)y_acima][x]  == 'b');
	}
	return result;
}

bool personagem_no_chao(Fase * fase, Vector2f * pos, float pLargura, float pAltura){
	// Margem de 0.1 porque o chão é no próximo tile.
	double y_abaixo  = pos->y + pAltura/2 + 0.1;
	int x_inicial = (int) (pos->x - pLargura/2 );
	int x_final   = (int) (pos->x + pLargura/2 );

	// Se ele não estiver logo logo acima, ele não conta como 'em cima'
	// do bloco. Senão ele pode só estar com o pé numa parede e contar
	// como 'em cima'. Como se estivesse no chocolate do transformice.
	if(y_abaixo - ((int)y_abaixo) >= 0.25)
		return false;

	// Um Mario caindo infinitamente provavelmente seria ruim.
	// Mas talvez ele tenha que cair quando morre (credo!)
	if(y_abaixo>= FASE_ALTURA-TILES_CHAO)
		return true;

	//  Passa por todos os x que estão diretamente abaixo do personagem.
	//  Se ele encontrar algum =='p', o resultado vai ser true.
	//  Quando encontrar, sai do loop .
	bool result = false;
	for(int x = x_inicial; x <= x_final && result == false; ++x){
		result |= (fase->mapa[(int)y_abaixo][x]  == 'p') || (fase->mapa[(int)y_abaixo][x]  == 'b');
	}
	return result;
}

// TODO: hardcode aleatório. Talvez ter um conjunto
// unificado de defines futuramente seja mais prudente
Rectangle mario_pos_to_screen_rect(Vector2 pos){
	Rectangle mario_rect = {
		.x = pos.x,
		.y = pos.y,
		.width = (int) (3.5 * 16),
		.height = (int) (3.5 * 21),
	};
	mario_rect.x -= mario_rect.width / 2;
	mario_rect.y -= mario_rect.height / 2;
	return mario_rect;
}

#endif /* FASES_C */
