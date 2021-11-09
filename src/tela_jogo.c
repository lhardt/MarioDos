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
    j->tela_jogo->fase.mario.vel.x = 0;
    j->tela_jogo->fase.mario.vel.y = 0.1;

    load_fases(& j->tela_jogo->fase, "fase1.txt");


}

// Se o mario quer pular de [4,2] para [5,5], temos que ver se não há
// nada que vá ser um chão ou parede para ele antes. Se tiver um chão
// em que o mario só consegue ficar de pé na altura 4, então o y final
// dele tem que ser 4. Nem 2 nem 5.    (Mesma coisa com paredes)
void conserta_nova_posicao(Fase * f, Vector2f * novaPosicao){
    Mario * mario = & f->mario;

    // TODO: aqui eu só supus que ele tá caindo (novaY > antigaY).
    // Talvez dê pra fazer um IF e dois FORs quase iguais, embora eu ache
    // mais raro de acotnecer (ele nunca vai pegar muita velocidade na subida)
    for(double y = mario->pos.y; y < novaPosicao->y; ++y){
        // Se no meio do caminho vertical tiver um bloco, ele deve parar antes.
        // printf("Vai acessar o mapa em [%d %d]", (int) (y+0.5), (int) (mario->pos.x + 0.5));
        if( f->mapa[ (int) (y + MARIO_ALTURA/2) ][ (int) (mario->pos.x) ]  == 'p'){
            // Se for uma plataforma, é uma altura 'antes' dessa,
            // Entrega a altura desfazendo um passo.
            novaPosicao->y = (int)y;
            // E se ele bateu no chão, ele perde a velocidade vertical.
            mario->vel.y = 0;
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

    conserta_nova_posicao(f, &novaPosicao);

    //if(){// se não tiver colisão
    mario->pos.x = novaPosicao.x;
    mario->pos.y = novaPosicao.y;
    //}
}

void telajogo_desenha(Jogo * j){
	ClearBackground(BLACK);

    fases_desenha(& j->tela_jogo->fase);

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
        fase_mario_no_chao(& j->tela_jogo->fase) ? GREEN : BLUE);


    textura_desenha(j, T_MARIO1, pos_mario);
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
        if(fase_mario_no_chao(& j->tela_jogo->fase)) {
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

    printf("Mario Pos: [%.2f , %.2f] Vel: [%.2f , %.2f] \n",
        mario->pos.x, mario->pos.y,
        mario->vel.x, mario->vel.y
    );

}

void telajogo_logica(Jogo * j){

    muda_posicao(& j->tela_jogo->fase);

    Mario * mario = & j->tela_jogo->fase.mario;

    if(mario->vel.y >= 0 && fase_mario_no_chao(& j->tela_jogo->fase)){
            mario->vel.y = 0;
    } else{
        if(mario->vel.y <= -GRAVIDADE && fase_mario_no_teto(& j->tela_jogo->fase)){
            mario->vel.y = GRAVIDADE;
        } else {
            mario->vel.y += GRAVIDADE;
        }
    }
}

void telajogo_termina(Jogo * j){
	free(j->tela_jogo);
	j->tela_jogo = NULL;
}
