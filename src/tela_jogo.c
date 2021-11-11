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



void telajogo_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_jogo = calloc(1, sizeof(TelaJogoInfo));
	j->tela_jogo->nMapa = 0;// Depois tem que mudar pra funcionar com os jogos carregados, mas por padr�o come�a em 0
    //j->tela_jogo->fase.mario.pos.x = 500;
    //j->tela_jogo->fase.mario.pos.y = 1000;
    j->tela_jogo->fase.mario.vel.x = 0;
    j->tela_jogo->fase.mario.vel.y = 0.1;
    j->tela_jogo->fase.inimigos[0].pos.x = 10;
    j->tela_jogo->fase.inimigos[0].pos.y = 7;
    j->tela_jogo->fase.inimigos[0].vel.x = 0.5;
    j->tela_jogo->fase.inimigos[0].vel.y = 0.5;

    load_fases(& j->tela_jogo->fase, "fase1.txt");


}

// Se o mario quer pular de [4,2] para [5,5], temos que ver se não há
// nada que vá ser um chão ou parede para ele antes. Se tiver um chão
// em que o mario só consegue ficar de pé na altura 4, então o y final
// dele tem que ser 4. Nem 2 nem 5.    (Mesma coisa com paredes)
void conserta_nova_posicao(Fase *f, Vector2f *vel, Vector2f * antigaPos, char tipo, Vector2f * novaPosicao){
    float pLargura, pAltura;
    switch(tipo){
        case 'M':
            pLargura = MARIO_LARGURA;
            pAltura = MARIO_ALTURA;
            break;
        case 'T':
            pLargura = TARTARUGA_LARGURA;
            pAltura = TARTARUGA_ALTURA;
        case 'C':
        break;
    }

    if (tipo!='M' && antigaPos->y>24){ //se for inimigo e estiver no chão
        //chegando fim direita embaixo
        printf("\nantigaPos->x+pLargura/2 %f", antigaPos->x+pLargura/2);
        if (vel->x>0 && antigaPos->x+pLargura/2 >FASE_LARGURA){
            novaPosicao->x = FASE_LARGURA - DIST_CANOS;

            printf("\nentrou direita");
            novaPosicao->y = ALTURA_CANOS;
            vel->x = vel->x *-1;// MUDAR DIREÇÃO?
        }
        //chegando fim esquerda embaixo
        printf("\nantigaPos->x-pLargura/2 %f", antigaPos->x-pLargura/2);
        if (vel->x<0 && antigaPos->x-pLargura/2 < 0){

                printf("\nentrou esquerda");
            novaPosicao->x = DIST_CANOS;
            novaPosicao->y = ALTURA_CANOS;
            vel->x = vel->x *-1;// MUDAR DIREÇÃO?
        }
        //

    }

    if(vel->y>0 && antigaPos->y+pAltura > (FASE_ALTURA-TILES_CHAO)){
        vel->y = 0;
        novaPosicao->y = FASE_ALTURA-TILES_CHAO - pAltura/2;
    }
    //chegando fim direita
    if (vel->x>0 && antigaPos->x+pLargura/2 >FASE_LARGURA){
        novaPosicao->x = 0 - pLargura/2;
    }
    //chegando fim esquerda
    if (vel->x<0 && antigaPos->x-pLargura/2 < 0){
        novaPosicao->x = FASE_LARGURA;
    }
    // TODO: aqui eu só supus que ele tá caindo (novaY > antigaY).
    // Talvez dê pra fazer um IF e dois FORs quase iguais, embora eu ache
    // mais raro de acotnecer (ele nunca vai pegar muita velocidade na subida)
    for(double y = antigaPos->y; y < novaPosicao->y; ++y){
        // Se no meio do caminho vertical tiver um bloco, ele deve parar antes.
        // printf("Vai acessar o mapa em [%d %d]", (int) (y+0.5), (int) (mario->pos.x + 0.5));
        if( f->mapa[ (int) (y + pAltura/2) ][ (int) (antigaPos->x) ]  == 'p'){
            // Se for uma plataforma, é uma altura 'antes' dessa,
            // Entrega a altura desfazendo um passo.
            novaPosicao->y = (int)y;
            // E se ele bateu no chão, ele perde a velocidade vertical.
            vel->y = 0;
        }
    }
    // TODO: ver se não há paredes também;
    // Sugiro testar com mapa personalizado (de preferencia com uma queda grande)

    // Se não teve que interferir, que bom :)

}

void muda_posicao(Fase *f){
    Mario * mario = & f->mario;
    Vector2f novaPosicao = mario->pos;

    // Nova posição teórica. Vemos se é possível na chamada abaixo
    novaPosicao.x += mario->vel.x;
    novaPosicao.y += mario->vel.y;

    conserta_nova_posicao(f, &mario->vel, &mario->pos, 'M', &novaPosicao);
    //if(){// se não tiver colisão
    mario->pos.x = novaPosicao.x;
    mario->pos.y = novaPosicao.y;
    //}



    for (int x=0; x<1/*f->n_inimigos*/;x++){

        Inimigo * inimigo = &f->inimigos[x];
        novaPosicao = inimigo->pos;
        novaPosicao.x += inimigo->vel.x;
        novaPosicao.y += inimigo->vel.y;
        if (inimigo->tipo==T_TARTARUGA){
            conserta_nova_posicao(f, &inimigo->vel, &inimigo->pos, 'T', &novaPosicao);
        }
        else if (inimigo->tipo==T_CARANGUEJO){
                TODO();
            //conserta_nova_posicao(f, &inimigo->vel, &inimigo->pos, TARTARUGA_LARGURA, TARTARUGA_ALTURA, &novaPosicao);
        }

        inimigo->pos.x = novaPosicao.x;
        inimigo->pos.y = novaPosicao.y;
    }
}

void telajogo_desenha(Jogo * j){
	ClearBackground(BLACK);

    fases_desenha(j);

    Mario * mario = & j->tela_jogo->fase.mario;
    Vector2 pos_mario = posfloat_para_tela(mario->pos);

    Rectangle mario_rect = {
        .x = pos_mario.x,
        .y = pos_mario.y,
        .width = (int) (4.5 * 16),
        .height = (int) (4.5 * 21),
    };
    mario_rect.x -= mario_rect.width / 2;
    mario_rect.y -= mario_rect.height / 2;


    DrawRectangleLines(mario_rect.x, mario_rect.y , mario_rect.width, mario_rect.height/2,
        fase_mario_no_teto(& j->tela_jogo->fase) ? GREEN : BLUE);


    DrawRectangleLines(mario_rect.x, mario_rect.y  + mario_rect.height/2, mario_rect.width, mario_rect.height/2,
        fase_no_chao(& j->tela_jogo->fase, & mario->pos, MARIO_LARGURA, MARIO_ALTURA) ? GREEN : BLUE);

    //Desenha mario
    if (mario->vel.x==0){
        textura_desenha(j, E_MARIO1, pos_mario);
    }
    else if(mario->vel.x<0) {
        textura_desenha(j, E_MARIO2, pos_mario);
    }
    else if(mario->vel.x>0) {
        textura_desenha(j, D_MARIO2, pos_mario);
    }


    TODO()
    //provisório, ta em uso só pra teste. tem que arrumar pra inicializar todos inimigos
    Inimigo * tartaruga = &j->tela_jogo->fase.inimigos[0];
    tartaruga->tipo = T_TARTARUGA;
    Vector2 pos_tar = posfloat_para_tela(tartaruga->pos);
    //printf("\n  vel pos tartaruga %f %f %f %f", tartaruga->vel.x, tartaruga->vel.y, tartaruga->pos.x, tartaruga->pos.y );
    //Desenha tartaruga
    if(tartaruga->vel.x>=0){
        textura_desenha(j, D_TARTARUGA2, pos_tar );
    }
    else{
        textura_desenha(j, E_TARTARUGA2, pos_tar );
    }

}

void telajogo_entrada(Jogo * j){
	TelaJogoInfo * tela = j->tela_jogo;
    Mario * mario = & j->tela_jogo->fase.mario;

    // A função mudaVelocidade não tinha muito valor agregado, era só mudar direto!
    // muda_velocidade(& j->tela_jogo->fase.mario, 0,-1);

    // NOTE: Aqui não precisa de else. Se eu segurar LEFT+RIGHT,
    // a consequência sem o else é ficar parado.
    // Com o ELSE, ele só ativaria o que vier primeiro no código.

    // NOTE2: IsKeyPressed detecta uma vez ao pressionar. IsKeyDown detecta até soltar.

    // Ele só se mexe para os lados se o jogador quiser. Total liberdade aí.
    // Então se ele não cair num dos IFs abaixo, o personagem não deve se mexer mesmo.
    mario->vel.x = 0;

    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_C)){
        if(fase_no_chao(& j->tela_jogo->fase, &mario->pos, MARIO_LARGURA, MARIO_ALTURA)) {
            mario->vel.y = -0.9;
        }
	}
    if(IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_LEFT)){
        mario->vel.x = 0.5;
	    printf("KEY_RIGHT\t");
	}
    if(IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_RIGHT)){
        mario->vel.x = -0.5;
	    printf("KEY_LEFT\t");
	}

    printf("\nMario Pos: [%.2f , %.2f] Vel: [%.2f , %.2f] \n",
        mario->pos.x, mario->pos.y,
        mario->vel.x, mario->vel.y
    );

}

//dar nome melhor
void logica(Fase * f, Vector2f * vel, Vector2f * pos, float pLargura, float pAltura){
    if(vel->y >= 0 && fase_no_chao(f, pos, pLargura, pAltura )){
            vel->y = 0;

    } else{
        if(vel->y <= -GRAVIDADE && fase_mario_no_teto( f)){
            vel->y = GRAVIDADE;
        } else {
            vel->y += GRAVIDADE;
        }
    }

}

void telajogo_logica(Jogo * j){

    muda_posicao(& j->tela_jogo->fase);

    Mario * mario = & j->tela_jogo->fase.mario;

    logica(&j->tela_jogo->fase, & mario->vel, &mario->pos, MARIO_LARGURA, MARIO_ALTURA);

    Inimigo * inimigo  = &j->tela_jogo->fase.inimigos[0];

    logica(&j->tela_jogo->fase, & inimigo->vel, & inimigo->pos, TARTARUGA_LARGURA, TARTARUGA_ALTURA);


}

void telajogo_termina(Jogo * j){
	free(j->tela_jogo);
	j->tela_jogo = NULL;
}
