#ifndef FASES_C
#define FASES_C

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "jogo.h"
#include "assert.h"
#include "tipos.h"

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
	f->mario.pos = (Vector2f) {5.0, 2.0};


	return true;
}

void tile_desenha(int x, int y, Color cor){
	DrawRectangle(x * TILE_LARGURA, y * TILE_ALTURA, TILE_LARGURA, TILE_ALTURA, cor);
}

Color tile_para_cor(char c){
	switch(c){
		case '-': return BLACK;
		case 'p': return BLUE;
		case 'm': return RED;
	}
	return BLACK;
}

void fases_desenha(Fase * f){
	// /* Teste: desenha as 4 bordas da tela. */
	// for(int i = 0; i < FASE_ALTURA; ++i){
	// 	tile_desenha(0,i, RED);
	// 	tile_desenha(119,i, RED);
	// }
	// for(int i = 0; i < FASE_LARGURA; ++i){
	// 	tile_desenha(i,0, RED);
	// 	tile_desenha(i,27, RED);
	// }
    for (int y=0; y < FASE_ALTURA; y++){
		for (int x=0; x<FASE_LARGURA; x++){
			tile_desenha(x,y, tile_para_cor(f->mapa[y][x]));
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

#endif /* FASES_C */
