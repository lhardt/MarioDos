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
		fscanf(entrada, "%d %d %d\n", &f->n_tartarugas, &f->n_carangueijos, &f->delay);
    }

	// Configura o Mario
	f->mario.vidas = 3;
	f->mario.score = 0;
	f->mario.pos = (Vector2f) {10, 5};
	f->n_inimigos = f->n_carangueijos +f->n_tartarugas;

	return true;
}

void tile_desenha(int x, int y, Color cor){
	DrawRectangle(x * TILE_LARGURA, y * TILE_ALTURA, TILE_LARGURA, TILE_ALTURA, cor);
}

Color tile_para_cor(char c){
	switch(c){
		case '-': return BLACK;
		case 'p': return BLUE;
		case 'm': return RED;//TIRAR E COLOCAR O MARIO
	}
	return BLACK;
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

			if (f->mapa[y][x] == 'c'){
                    Vector2 pos = {.x = x, .y = y};//  AQUIIIII, não consegui acertar o posicionamento e meu cérebro já está uma ameba
                if (x> FASE_LARGURA/2){//se for desenhar na parte direita da tela
                    printf ("\ndesenhou D");
                    textura_desenha(j,D_CANO, pos);
                }
                else{
                        printf ("\ndesenhou E");
                    textura_desenha(j,E_CANO, pos);
                }
			}
			else if(f->mapa[y][x] == 'b'){
                TODO();
			}
			else if(f->mapa[y][x] == 'm'){
                TODO();
			}
			else{
                tile_desenha(x,y, tile_para_cor(f->mapa[y][x]));
			}
	    }
    }

    for (int y=FASE_ALTURA-TILES_CHAO; y < FASE_ALTURA; y++){
		for (int x=0; x<FASE_LARGURA; x++){
			tile_desenha(x,y, MAROON);
	    }
    }

}

bool fases_inicia(Jogo * j){
	TODO();
    return true;
}

void fases_termina(Jogo * j){
	TODO();
}

bool fase_mario_no_teto(Fase * fase){
	Vector2f pos_mario = fase->mario.pos;

	// Margem de 0.1 porque o chão é no próximo tile.
	double y_acima  = pos_mario.y - MARIO_ALTURA/2 - 0.1;
	int x_inicial = (int) (pos_mario.x - MARIO_LARGURA/2 );
	int x_final   = (int) (pos_mario.x + MARIO_LARGURA/2 );

	bool result = false;
	for(int x = x_inicial; x <= x_final && result == false; ++x){
		result |= (fase->mapa[(int)y_acima][x]  == 'p');
	}
	return result;

}

bool fase_no_chao(Fase * fase, Vector2f * pos, float pLargura, float pAltura){


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

	// Só para fazer sentido: deleta esse comentário depois:
	//  Passa por todos os x que estão diretamente abaixo do Mario.
	//  Se ele encontrar algum =='p', o resultado vai ser true.
	//  Quando encontrar, sai do loop (olha a condição do for).
	bool result = false;
	for(int x = x_inicial; x <= x_final && result == false; ++x){
		result |= (fase->mapa[(int)y_abaixo][x]  == 'p');
	}
	return result;
}

// TODO: hardcode aleatório. Talvez ter um conjunto
// unificado de defines futuramente seja mais prudente
Rectangle mario_pos_to_screen_rect(Vector2 pos){
	Rectangle mario_rect = {
		.x = pos.x,
		.y = pos.y,
		.width = (int) (4.5 * 16),
		.height = (int) (4.5 * 21),
	};
	mario_rect.x -= mario_rect.width / 2;
	mario_rect.y -= mario_rect.height / 2;
	return mario_rect;
}

#endif /* FASES_C */
