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
	//TEMPORIARIO
    char * enderecoFase = malloc(strlen(CAMINHO_FASES)+ strlen(arquivo)+1);

    sprintf(enderecoFase, "%s%s", CAMINHO_FASES, arquivo);

    FILE * entrada = fopen(enderecoFase, "r");

    if (entrada == NULL){ printf ("Arquivo não encontrado"); }
    char teste[3];

    while(!feof(entrada)){
        for (int x=0; x<FASE_ALTURA+1; x++){
                //printf("\n x %d", x);
            if (x == FASE_ALTURA){
                    //printf ("entrou aqui");
                fscanf(entrada, "%5[^\n]\n", teste);//fscanf(entrada, );// PEGAR OS TRES NUMEROS DO FIM
                //printf("\nteste Q%sQ", teste);
            }
            else{
                fscanf(entrada, "%120[^\n]\n", f->mapa[x]);
                //printf("\nx%d%sf", x, f->mapa[x]);
            }

            //printf("\n%s", f->mapa[x]);
        }

    }
    for (int x =0;x<FASE_ALTURA;x++){
        printf("\ni%sf", f->mapa[x]);
    }

	return true;
}

void fases_desenha(Fase * f){



    Vector2 pos;
	pos.x = 0;
	pos.y = 0;
    printf("linha%sfim", f->mapa[0]);
	/*for (int x =0;x<FASE_ALTURA;x++){
            printf("\n");
        for (int y; y<FASE_LARGURA;y++){
            printf("%s", f->mapa[x][y]);
        }
	}*/
    for (int x=0; x<FASE_ALTURA; x++){
            //printf("\n");
        for (int y=0; y< FASE_LARGURA; y++){
            if(f->mapa[x][y]=='-'){
                //printf("test1");
                DrawRectangle(pos.x, pos.y, TILE_LARGURA, TILE_ALTURA, GREEN);
            }
            else if(f->mapa[x][y]=='p'){

                DrawRectangle(pos.x, pos.y, TILE_LARGURA, TILE_ALTURA, BLUE);
            }
            else if(f->mapa[x][y]=='s'){
                DrawRectangle(pos.x, pos.y, TILE_LARGURA, TILE_ALTURA, RED);
            }
            //printf("%c", f->mapa[x][y]);
            pos.y += TILE_LARGURA;
        }

        pos.y=0;
        pos.x+= TILE_ALTURA;
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
