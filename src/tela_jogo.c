/**
 * MarioDos.
 *   tela_jogo.c - tela de jogo do jogo.
 *
 * (C) 2021 Ana Laura e L�o Hardt.
 *
 * Este arquivo cont�m as defini��es da tela de jogo do jogo.
 * � nesta tela em que o mapa do jogo � montado e o usu�rio pode
 * come�ar a jogar.
 */
#include "jogo.h"
#include "textura.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include <math.h>

struct TelaJogoInfo {
    Fase fase;
    int nMapa;
};

void telajogo_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_jogo = calloc(1, sizeof(TelaJogoInfo));
	j->tela_jogo->nMapa = 0;// Depois tem que mudar pra funcionar com os jogos carregados, mas por padr�o come�a em 0
    j->tela_jogo->fase.mario.pos.x = 500;
    j->tela_jogo->fase.mario.pos.y = 1000;
    j->tela_jogo->fase.mario.velocidadeX =0;
    j->tela_jogo->fase.mario.velocidadeY=0;

    load_fases(& j->tela_jogo->fase, "fase1.txt");


}
/*void muda_pos_vertical(Fase * f){

    Mario * mario = & f->mario;
    if (pos<0){
        (mario->pos.y) += pos;
    }
    else {
            int x = round(mario->pos.x);
            int y = round(mario->pos.y);
            printf("x y m %d %d %c \n", x, y, f->mapa[x][y]);
        if (f->mapa[x][y]!= 'p'){
            (mario->pos.y) += pos;
        }
    }
}*/

void muda_posicao(Fase *f){
    Mario * mario = & f->mario;
    //if(){// se não tiver colisão
        mario->pos.x += mario->velocidadeX;
        mario->pos.y += mario->velocidadeY;

        printf("\npx %f py %f", mario->pos.x, mario->pos.y);

        printf("\nvx %f vy %f", mario->velocidadeX, mario->velocidadeY);
    //}
}
void muda_velocidade(Mario *mario, float vx, float vy){
    printf ("vxx %f vyy %f", vx, vy);
    mario->velocidadeX +=vx;
    mario->velocidadeY +=vy;
    /*if (mario->velocidadeX>2){
        mario->velocidadeX -=vx;
    }*/
    /*else if(mario->velocidadeX<0){
        mario->velocidadeX=0;
    }*/
    printf("\nmvx %f vy %f", mario->velocidadeX, mario->velocidadeY);
}

void telajogo_desenha(Jogo * j){
	ClearBackground(BLACK);

    fases_desenha(& j->tela_jogo->fase);

    Mario * mario = & j->tela_jogo->fase.mario;
    Vector2 pos_mario = posfloat_para_tela(mario->pos);
    //textura_desenha(j, T_MARIO1, (Vector2){.x=150, .y=190});
    //muda_pos_vertical(& j->tela_jogo->fase, 0.125);
    //muda_velocidade(mario, 0,0.05);
    //muda_posicao(& j->tela_jogo->fase);

    textura_desenha(j, T_MARIO1, pos_mario);
}



void telajogo_entrada(Jogo * j){
	//TelaJogoInfo * tela = j->tela_jogo;
	//printf("tela jogo entrada");
	if (IsKeyPressed(KEY_UP)){//a principio quem pula é C
            printf("KEY_UP");
        for (int x=0; x<5;x++){
            //printf ("pos x %f", (j->tela_jogo->fase.mario.pos.y) );
            //(j->tela_jogo->fase.mario.pos.y) -= 0.125;
            //muda_pos_vertical(& j->tela_jogo->fase, -0.125);

            muda_velocidade(& j->tela_jogo->fase.mario, 0,-1);
            muda_posicao(& j->tela_jogo->fase);
        }
	}
	else if(IsKeyPressed(KEY_DOWN)){
            printf("KEY_DOWN");
	}

	else if(IsKeyPressed(KEY_RIGHT)){
	    printf("KEY_RIGHT");
	}
	else if(IsKeyPressed(KEY_LEFT)){
	    printf("KEY_LEFT");
        for (int x=0; x<20;x++){
            //printf ("pos x %f", (j->tela_jogo->fase.mario.pos.y) );
            //(j->tela_jogo->fase.mario.pos.y) -= 0.125;

        }
	}
	else if (IsKeyPressed(KEY_C)){
        printf("KEY_C");
    }
}

void telajogo_logica(Jogo * j){

}

void telajogo_termina(Jogo * j){
	free(j->tela_jogo);
	j->tela_jogo = NULL;
}
