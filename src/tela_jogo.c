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
#include <time.h>

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

void cria_inimigo(Fase * f, Inimigo * retval){
	// TODO: acredito que tenhamos que trocar de cano,

	retval->pos.y = 7.5;
	retval->vel.y = 0.5;

	int alternado_aleatorio = (1 + (rand() % 100)) % 2;


    //se ainda tiverem caranguejos e tartarugas a serem criadas, sorteia qual vai ser
    if (f->n_caranguejos>0 && f->n_tartarugas>0){
        if (alternado_aleatorio){
            retval->tipo = T_CARANGUEJO;
        } else{
            retval->tipo = T_TARTARUGA;
        }
    }else{//caso contrário, seleciona o tipo
        if (f->n_caranguejos>0){
            retval->tipo = T_CARANGUEJO;
        }
        else if(f->n_tartarugas>0){
            retval->tipo = T_TARTARUGA;
        }
    }

    if(retval->tipo==T_CARANGUEJO){
        retval->vulnerabilidade= V_FURIOSO;
        retval->vel.x = 0.3 * f->n_mapa;
        (f->n_caranguejos)--;
    }
    else{
        retval->vulnerabilidade= V_INVULNERAVEL;
        retval->vel.x = 0.2;
        (f->n_tartarugas)--;
    }

    //Seleciona posição e direção inicial
    alternado_aleatorio = (1 + (rand() % 100)) % 2;

    if (alternado_aleatorio){
        retval->pos.x = 11;
    }
    else{
        retval->vel.x = (retval->vel.x)*-1;
        retval->pos.x = 100;
    }

	retval->vivo = true;
}

void desenha_inimigo(Jogo * j, Inimigo * inimigo){
	Vector2 pos_inimigo = posfloat_para_tela(inimigo->pos);

    if (inimigo->vivo){
        if(inimigo->tipo == T_TARTARUGA){
            if(inimigo->vulnerabilidade== V_VULNERAVEL){
                textura_desenha(j, TARTARUGA_V, pos_inimigo );
            }else{
                if(inimigo->vel.x>=0){
                    textura_desenha(j, D_TARTARUGA2, pos_inimigo );
                } else {
                    textura_desenha(j, E_TARTARUGA2, pos_inimigo );
                }
            }
        }else if(inimigo->tipo == T_CARANGUEJO){
            if(inimigo->vulnerabilidade== V_VULNERAVEL){
                textura_desenha(j, CARANGUEJO_V, pos_inimigo );
            }else if (inimigo->vulnerabilidade==V_FURIOSO){
                if(inimigo->vel.x>=0){
                    textura_desenha(j, D_CARANGUEJO_F, pos_inimigo );
                }
                else{
                    textura_desenha(j, E_CARANGUEJO_F, pos_inimigo );
                }
            }else{
                if(inimigo->vel.x>=0){
                    textura_desenha(j, D_CARANGUEJO_I, pos_inimigo );
                }
                else{
                    textura_desenha(j, E_CARANGUEJO_I, pos_inimigo );
                }
            }
        }
    }
}

void telajogo_inicia(Jogo * j){
	// NOTE: a função calloc garante que tudo será
	// inicializado com 0000, então todas as outras
	// opções estarão em branco.
	j->tela_jogo = calloc(1, sizeof(TelaJogoInfo));
	j->tela_jogo->fase.n_mapa = j->num_fase;

    j->tela_jogo->fase.mario.vel.x = 0;
    j->tela_jogo->fase.mario.vel.y = 0.1;

    j->tela_jogo->fase.n_inimigos =0;
    j->tela_jogo->fase.n_moedas =0;

	srand(time(NULL));
	//j->tela_jogo->fase.n_inimigos = 1;

	load_fases(& j->tela_jogo->fase, j->nome_fase);


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
        case 'D':
            pLargura = MOEDA_LARGURA;
            pAltura = MOEDA_ALTURA;
    }

    if (tipo != 'M' && antigaPos->y > 24){ //se for inimigo ou moeda e estiver no chão
        //chegando fim direita embaixo
        if (vel->x>0 && antigaPos->x+pLargura/2 >FASE_LARGURA){
            novaPosicao->x = FASE_LARGURA - DIST_CANOS;
            novaPosicao->y = ALTURA_CANOS;
            vel->x = vel->x *-1;// MUDAR DIREÇÃO
        }
        //chegando fim esquerda embaixo
        if (vel->x<0 && antigaPos->x-pLargura/2 < 0){
            novaPosicao->x = DIST_CANOS;
            novaPosicao->y = ALTURA_CANOS;
            vel->x = vel->x *-1;// MUDAR DIREÇÃO
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

    for (int x=0; x < f->n_moedas;x++){
        Moeda * moeda = &f->moedas[x];
        novaPosicao = moeda->pos;
        novaPosicao.x += moeda->vel.x;
        novaPosicao.y += moeda->vel.y;

        conserta_nova_posicao(f, &moeda->vel, &moeda->pos,'D', &novaPosicao);

        moeda->pos.x = novaPosicao.x;
        moeda->pos.y = novaPosicao.y;
    }

}

void desenha_moeda(Jogo *j, Moeda * moeda){
    Vector2 pos_moeda = posfloat_para_tela(moeda->pos);
    if (!(moeda->coletada)){
        if(j->ticks %5 ==0){
            textura_desenha(j, MOEDA1, pos_moeda);
        }
        else{
            textura_desenha(j, MOEDA2, pos_moeda );
        }

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
	for(int i = 0; i < j->tela_jogo->fase.n_moedas; ++i){
		desenha_moeda(j, &j->tela_jogo->fase.moedas[i]);
	}

}

void telajogo_entrada(Jogo * j){
	TelaJogoInfo * tela = j->tela_jogo;
    Mario * mario = & j->tela_jogo->fase.mario;


    // NOTE: Aqui não precisa de else. Se eu segurar LEFT+RIGHT,
    // a consequência sem o else é ficar parado.
    // Com o ELSE, ele só ativaria o que vier primeiro no código.

    // NOTE2: IsKeyPressed detecta uma vez ao pressionar. IsKeyDown detecta até soltar.

    // Ele só se mexe para os lados se o jogador quiser. Total liberdade aí.
    // Então se ele não cair num dos IFs abaixo, o personagem não deve se mexer mesmo.
    mario->vel.x = 0;

    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_D)){
        if(personagem_no_chao(& j->tela_jogo->fase, &mario->pos, MARIO_LARGURA, MARIO_ALTURA)) {
            mario->vel.y = -0.9;
        }
	}
    if(IsKeyDown(KEY_RIGHT) && IsKeyUp(KEY_LEFT)){
        mario->vel.x = 0.5;
	    //printf("KEY_RIGHT\t");
	}
    if(IsKeyDown(KEY_LEFT) && IsKeyUp(KEY_RIGHT)){
        mario->vel.x = -0.5;
	    //printf("KEY_LEFT\t");
	}

    /*printf("\nMario Pos: [%.2f , %.2f] Vel: [%.2f , %.2f] \n",
        mario->pos.x, mario->pos.y,
        mario->vel.x, mario->vel.y
    );*/

}

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

bool inimigo_na_posicao(Inimigo * inimigo, Vector2f * pos_mario){//pegar tiles acima do mario, ver se personagem está logo acima dele
    int xm_inicial = (int) (pos_mario->x - MARIO_LARGURA/2 );
	int xm_final   = (int) (pos_mario->x + MARIO_LARGURA/2 );
	double y_acima_m  = pos_mario->y - MARIO_ALTURA/2 - 0.1;
	int pAltura;

	int xi_inicial, xi_final;

	if (inimigo->tipo == T_TARTARUGA){
        pAltura = TARTARUGA_ALTURA;
        xi_inicial = (int) (inimigo->pos.x - TARTARUGA_LARGURA/2);
        xi_final = (int) (inimigo->pos.x - TARTARUGA_LARGURA/2);
	}else{
	    pAltura = CARANGUEJO_ALTURA;
        xi_inicial = (int) (inimigo->pos.x - CARANGUEJO_LARGURA/2);
        xi_final = (int) (inimigo->pos.x - CARANGUEJO_LARGURA/2);
	}

	double y_abaixo  = inimigo->pos.y + pAltura/2 + 0.1;
	if(y_abaixo - ((int)y_abaixo) >= 0.25){
		return false;}


	if ((int) y_acima_m == ((int) y_abaixo) +1){//MARACUTAIA pra funcionar
        if((xi_inicial>= xm_inicial && xi_inicial<=xm_final) //se a posicao final do inimigo estiver entre as do mario
         || (xi_final>= xm_inicial && xi_final<=xm_final))// ou se a posicao inicial do inimigo estiver entre as do mario
           {
            return true;
        }
	}
	return false;

}

bool mario_colide(Vector2f pos_mario, Vector2f pos_p, int largura, int altura){
    int xm_inicial = (int) (pos_mario.x - MARIO_LARGURA/2 );
	int xm_final   = (int) (pos_mario.x + MARIO_LARGURA/2 );
    int ym_inicial = (int) (pos_mario.y - MARIO_ALTURA/2 );
	int ym_final   = (int) (pos_mario.y + MARIO_ALTURA/2 );

    int xp_inicial = (int) (pos_p.x - largura/2 );
	int xp_final   = (int) (pos_p.x + largura/2 );
    int yp_inicial = (int) (pos_p.y - altura/2 );
	int yp_final   = (int) (pos_p.y + altura/2 );

    if ((xm_inicial<=xp_final && xm_inicial>=xp_inicial)
        || (xm_final>=xp_inicial && xm_final<=xp_final )){
        if ((ym_inicial<=yp_final && ym_inicial>=yp_inicial)
             || (ym_final<=yp_final && ym_final>=yp_inicial)){
            return true;
        }
    }
    return false;
}

void tipo_largura_altura(double * largura, double *altura, Inimigo * inimigo){
    if (inimigo->tipo== T_TARTARUGA){
            *largura = TARTARUGA_LARGURA;
            *altura = TARTARUGA_ALTURA;
    }else{
        *largura = CARANGUEJO_LARGURA;
        *altura = CARANGUEJO_ALTURA;
    }
}

void cria_moeda(Fase * f, Moeda * moeda ){
    moeda->pos.y = 7.5;
	moeda->vel.y = 0.5;
	moeda->vel.x = 0.3 * f->n_mapa;
    int alternado_aleatorio = (1 + (rand() % 100)) % 2;
    moeda->coletada = false;

    if (alternado_aleatorio){
        moeda->pos.x = 11;
    }
    else{
        moeda->vel.x = (moeda->vel.x)*-1;
        moeda->pos.x = 100;
    }
}

void muda_vulnerabilidade(Jogo *j, Inimigo * i){

    if (i->vulnerabilidade == V_FURIOSO){// O CARANGUEJO TÁ INDO DIRETO DE FURIOSO PRA VULNERÁVEL
        // E EU ACHO QUE É PORQUE A FUNÇÃO É EXECUTADA DUAS VEZES NA MESMA POSIÇÃO, VIDE OS PONTOS AO BATER NUM CARANGUEJO
        i->vulnerabilidade = V_INVULNERAVEL;
        (j->pontos) +=10;
        i->vel.x = i->vel.x*0.7;// velocidade é 70% da velocidade original
    }
    else if (i->vulnerabilidade == V_INVULNERAVEL){
        i->vulnerabilidade = V_VULNERAVEL;
        i->vel.x =0;
        (j->pontos) +=10;
    }
}

void telajogo_logica(Jogo * j){
	Fase * f = & j->tela_jogo->fase;

    muda_posicao(f);

    Mario * mario = & f->mario;

	// Aumenta o número de inimigos.

	// NOTE: n_ticks está em 1/60 de segundo
	if(j->ticks % (f->delay * 60) == 0 && (f->n_caranguejos>0 || f->n_tartarugas>0 )){
		int * n_inimigos_ptr = & j->tela_jogo->fase.n_inimigos;
		cria_inimigo(& j->tela_jogo->fase, & j->tela_jogo->fase.inimigos[*n_inimigos_ptr]);
          ++(*n_inimigos_ptr);
	}
    // Aumenta o número de moedas.
	if(j->ticks % (f->delay * 80) == 0 && f->n_moedas< (f->n_caranguejos + f->n_tartarugas + f->n_inimigos)){
		int * n_moedas_ptr = & j->tela_jogo->fase.n_moedas;
		cria_moeda(& j->tela_jogo->fase, & j->tela_jogo->fase.moedas[*n_moedas_ptr]);
        (*n_moedas_ptr) +=1;
	}

    //testa se mario bateu na plataforma onde acima está um inimigo e faz a lógica
	for (int i=0; i<f->n_inimigos;i++){
        if(personagem_no_teto(f, &mario->pos, MARIO_LARGURA, MARIO_ALTURA)
           && inimigo_na_posicao(&f->inimigos[i], &mario->pos) && f->inimigos[i].vivo){
            muda_vulnerabilidade(j, &f->inimigos[i]);
        }
	}
    //Lógica botão power
	if(mario_no_power(f) && j->ticks % 5 ==0 && j->num_power<NMAX_POWER){
        for (int i=0; i<f->n_inimigos;i++){
            if(f->inimigos[i].vulnerabilidade!=V_VULNERAVEL){
                muda_vulnerabilidade(j, &f->inimigos[i] );
            }
        }
        for (int i=0; i<f->n_moedas;i++){
            if (!(f->moedas[i].coletada)){
                f->moedas[i].coletada = true;
                j->pontos +=1;
            }
        }
        (j->num_power) +=1;
    }

    // Muda velocidades
    muda_velocidade(f, & mario->vel, &mario->pos, MARIO_LARGURA, MARIO_ALTURA);

    for(int i = 0; i < f->n_moedas; ++i){
		Moeda * moeda  = &j->tela_jogo->fase.moedas[i];
        muda_velocidade(&j->tela_jogo->fase, & moeda->vel, & moeda->pos, MOEDA_LARGURA, MOEDA_ALTURA);

	}

	for(int i = 0; i < f->n_inimigos; ++i){
		Inimigo * inimigo  = &j->tela_jogo->fase.inimigos[i];
		if (inimigo->tipo==T_TARTARUGA){
            muda_velocidade(&j->tela_jogo->fase, & inimigo->vel, & inimigo->pos, TARTARUGA_LARGURA, TARTARUGA_ALTURA);
		}
		else{
            muda_velocidade(&j->tela_jogo->fase, & inimigo->vel, & inimigo->pos, CARANGUEJO_LARGURA, CARANGUEJO_ALTURA);
		}

	}

    //Lógica colisão inimigos
	for (int i=0; i< f->n_inimigos;i++){
        double largura, altura;
        tipo_largura_altura(&largura,&altura, &f->inimigos[i]);
        if (mario_colide(mario->pos, f->inimigos[i].pos,largura,altura) && (f->inimigos[i].vulnerabilidade==V_VULNERAVEL)
            && f->inimigos[i].vivo==true){
             f->inimigos[i].vivo=false;
            (j->pontos) +=800;
        }
        else if(j->ticks % 20 == 0 && mario_colide(mario->pos, f->inimigos[i].pos,largura,altura) && !(f->inimigos[i].vulnerabilidade==V_VULNERAVEL)){
            mario->vidas -=1;

        }
	}

	//Lógica colisão moedas
	for (int i=0; i< f->n_moedas;i++){
        if (mario_colide(mario->pos, f->moedas[i].pos,MOEDA_LARGURA, MOEDA_ALTURA) && !(f->moedas[i].coletada)){
            f->moedas[i].coletada = true;
            (j->pontos) +=100;
        }
	}

	//Lógica fase termina
	int fase_terminou = true;
	if ((f->n_caranguejos>0 || f->n_tartarugas>0) && mario->vidas>=0){
        fase_terminou = false;
	}
	for(int i=0;i< (f->n_inimigos);i++){
        if((f->inimigos[i].vivo==true) && mario->vidas>=0){
            fase_terminou = false;
        }
	}
	if (fase_terminou == true){
        if (j->num_fase==1 && mario->vidas>=0){
            j->num_fase=2;
            strcpy(j->nome_fase, "fase2.txt");
            jogo_troca_tela(j, TELA_JOGO);
        }
        else{
            jogo_troca_tela(j, TELA_HIGHSCORE);
        }
	}

}

void telajogo_termina(Jogo * j){
	highscore_salva(j);

	free(j->tela_jogo);
	j->tela_jogo = NULL;
}
