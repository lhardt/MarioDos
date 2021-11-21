/**
 * MarioDos.
 *   tela_informacoes.c -  .
 *  tela utilizada tanto para exibir a tela 'Ajuda'
 *  para o usuário quanto a tela 'Sobre'
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 *
 */

#include "jogo.h"
#include "textura.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 500

struct TelaInformacoesInfo {
    char texto[3][TAM_MAX];
};

void telainformacoes_inicia(Jogo * j){
    j->tela_informacoes = calloc(1, sizeof(TelaInformacoesInfo));
    if (j->num_fase==0){
        strcpy(j->tela_informacoes->texto[0], "Utilize as setas para controlar o Mario. Voce pode tambem pular ");
        strcpy(j->tela_informacoes->texto[1], "utilizando tanto  a seta quanto com a tecla D. Use a tecla 'A'");
        strcpy(j->tela_informacoes->texto[2], " para salvar o estado atual do jogo para terminar ele mais tarde.");
    }
    else{
        strcpy(j->tela_informacoes->texto[0], "Trabalho desenvolvido a partir do jogo 'Mario Bros.', de 1983,");
        strcpy(j->tela_informacoes->texto[1], "para a cadeira 'Algoritmos e Programacao', ministrada pelo");
        strcpy(j->tela_informacoes->texto[2], "professor Marcelo Walter no semestre letivo 2021/01 na UFRGS.");
    }

}

void telainformacoes_desenha(Jogo * j){
    ClearBackground(BLACK);
    texto_centralizado(j->fonte_menu, j->tela_informacoes->texto[0], (Vector2){.x=600,.y=200}, WHITE );
    texto_centralizado(j->fonte_menu, j->tela_informacoes->texto[1], (Vector2){.x=600,.y=300}, WHITE );
    texto_centralizado(j->fonte_menu, j->tela_informacoes->texto[2], (Vector2){.x=600,.y=400}, WHITE );
    texto_centralizado(j->fonte_menu, "Pressione ENTER para voltar ao menu!", (Vector2){.x=600,.y=600}, WHITE );
}

void telainformacoes_entrada(Jogo *j){
    TelaInformacoesInfo * tela = j->tela_informacoes;

    if (IsKeyPressed(KEY_ENTER)){
        jogo_troca_tela(j, TELA_MENU);
    }
}

void telainformacoes_logica(Jogo * j){

}

void telainformacoes_termina(Jogo * j){
	free(j->tela_informacoes);
	j->tela_informacoes = NULL;
}
