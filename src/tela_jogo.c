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
#include "assert.h"
#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>
#include <math.h>

void desenha_mario(Jogo * j, Mario * mario){

	Vector2 pos_mario = posfloat_para_tela(mario->pos);

	Rectangle mario_rect = {
        .x = pos_mario.x,
        .y = pos_mario.y,
        .width = (int) (3.5 * 16),
        .height = (int) (3.5 * 21),
    };
    mario_rect.x -= mario_rect.width / 2;
    mario_rect.y -= mario_rect.height / 2;

    DrawRectangleLines(mario_rect.x, mario_rect.y , mario_rect.width, mario_rect.height/2,
        personagem_no_teto(& j->tela_jogo->fase, & mario->pos, MARIO_LARGURA, MARIO_ALTURA) ? GREEN : BLUE);


    DrawRectangleLines(mario_rect.x, mario_rect.y  + mario_rect.height/2, mario_rect.width, mario_rect.height/2,
        personagem_no_chao(& j->tela_jogo->fase, & mario->pos, MARIO_LARGURA, MARIO_ALTURA) ? GREEN : BLUE);

	if (mario->vel.x==0){
        textura_desenha(j, E_MARIO1, pos_mario);
    }
    else if(mario->vel.x<0) {
        textura_desenha(j, E_MARIO2, pos_mario);
    }
    else if(mario->vel.x>0) {
        textura_desenha(j, D_MARIO2, pos_mario);
    }

}

void desenha_inimigo(Jogo * j, Inimigo * inimigo){
	Vector2 pos_inimigo = posfloat_para_tela(inimigo->pos);

	if(inimigo->tipo == T_TARTARUGA){
		if(inimigo->vel.x>=0){
			textura_desenha(j, D_TARTARUGA2, pos_inimigo );
		} else {
			textura_desenha(j, E_TARTARUGA2, pos_inimigo );
		}
	} else if(inimigo->tipo == T_CARANGUEJO){
		textura_desenha(j, E_CARANGUEJO, pos_inimigo );
	}
}

void cria_inimigo(Fase * f, Inimigo * retval, TipoInimigo tipo){
	// TODO: acredito que tenhamos que trocar de cano,
	retval->pos.x = 10;
	retval->pos.y = 7;
	retval->tipo = tipo;
	switch(tipo){
		case T_TARTARUGA:
			retval->vel.x = 0.5;
			retval->vel.y = 0.5;
			break;
		case T_CARANGUEJO:
			retval->vel.x = 0.5;
			retval->vel.y = 0.5;
			break;
	}
	retval->vivo = true;
}

void telajogo_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_jogo = calloc(1, sizeof(TelaJogoInfo));
	j->tela_jogo->fase.n_mapa = 1;// Depois tem que mudar pra funcionar com os jogos carregados, mas por padr�o come�a em 0
    //j->tela_jogo->fase.mario.pos.x = 500;
    //j->tela_jogo->fase.mario.pos.y = 1000;
    j->tela_jogo->fase.mario.vel.x = 0;
    j->tela_jogo->fase.mario.vel.y = 0.1;

	cria_inimigo(& j->tela_jogo->fase, & j->tela_jogo->fase.inimigos[0], T_CARANGUEJO);
	j->tela_jogo->fase.n_inimigos = 1;

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
			break;
        case 'C':
            pLargura = CARANGUEJO_LARGURA;
            pAltura = CARANGUEJO_ALTURA;
	        break;
    }

    if (tipo != 'M' && antigaPos->y > 24){ //se for inimigo e estiver no chão
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

    mario->pos.x = novaPosicao.x;
    mario->pos.y = novaPosicao.y;

    for (int x=0; x < f->n_inimigos;x++){

        Inimigo * inimigo = &f->inimigos[x];
        novaPosicao = inimigo->pos;
        novaPosicao.x += inimigo->vel.x;
        novaPosicao.y += inimigo->vel.y;

		conserta_nova_posicao(f, &inimigo->vel, &inimigo->pos,
			inimigo->tipo==T_TARTARUGA ? 'T' : 'C', &novaPosicao);

        inimigo->pos.x = novaPosicao.x;
        inimigo->pos.y = novaPosicao.y;
    }
}

void telajogo_desenha(Jogo * j){
	ClearBackground(BLACK);

    fases_desenha(j);

    Mario * mario = & j->tela_jogo->fase.mario;

	//Desenha mario
	desenha_mario(j, mario);

	int n_inimigos = j->tela_jogo->fase.n_inimigos;

	for(int i = 0; i < n_inimigos; ++i){
		desenha_inimigo(j, &j->tela_jogo->fase.inimigos[i]);
	}
    // //printf("\n  vel pos tartaruga %f %f %f %f", tartaruga->vel.x, tartaruga->vel.y, tartaruga->pos.x, tartaruga->pos.y );
    // //Desenha tartaruga

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
        if(personagem_no_chao(& j->tela_jogo->fase, &mario->pos, MARIO_LARGURA, MARIO_ALTURA)) {
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
void muda_velocidade(Fase * f, Vector2f * vel, Vector2f * pos, float pLargura, float pAltura){
    if(vel->y >= 0 && personagem_no_chao(f, pos, pLargura, pAltura )){
        vel->y = 0;
    } else{
        if(vel->y <= -GRAVIDADE && personagem_no_teto(f, pos, pLargura, pAltura)){
            vel->y = GRAVIDADE;
        } else {
            vel->y += GRAVIDADE;
        }
    }
}

void telajogo_logica(Jogo * j){
	Fase * f = & j->tela_jogo->fase;

    muda_posicao(f);

    Mario * mario = & f->mario;

    muda_velocidade(f, & mario->vel, &mario->pos, MARIO_LARGURA, MARIO_ALTURA);

	for(int i = 0; i < f->n_inimigos; ++i){
		Inimigo * inimigo  = &j->tela_jogo->fase.inimigos[i];
		muda_velocidade(&j->tela_jogo->fase, & inimigo->vel, & inimigo->pos, TARTARUGA_LARGURA, TARTARUGA_ALTURA);
	}

	// Aumenta o número de inimigos.

	// NOTE: n_ticks está em 1/60 de segundo
	if(j->ticks % (f->delay * 60) == 0 && f->n_inimigos < 10){
		int * n_inimigos_ptr = & j->tela_jogo->fase.n_inimigos;

		// TODO:
		// na verdade, aqui ele tem que decidir
		// 1. tem que criar carangueijo?
		// 2. tem que criar tartaruga?
		// se alguma é sim, cria uma
		// Aqui só estou usando o < 10 pra não ter 10000 inimigos na tela
		// e errar a memória.

		int alternado_aleatorio = (j->ticks / (f->delay * 60)) % 2;
		cria_inimigo(& j->tela_jogo->fase, & j->tela_jogo->fase.inimigos[*n_inimigos_ptr],
			alternado_aleatorio ? T_CARANGUEJO : T_TARTARUGA);

		++(*n_inimigos_ptr);
	}

}

void telajogo_termina(Jogo * j){
	free(j->tela_jogo);
	j->tela_jogo = NULL;
}
