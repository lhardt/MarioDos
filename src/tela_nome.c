/**
 * MarioDos.
 *   tela_carrega.c - tela de entrada do arquivo.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém as definições da tela de menu do jogo.
 * é nesta tela em que o jogo inicia, e nela o usuário pode
 * escolher jogar, carregar mapas, etc.
 */

#include "jogo.h"
#include "textura.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 10

struct TelaNomeInfo {
    char nome[TAM_MAX];
    int nChar;
};

void telanome_inicia(Jogo * j){
    j->tela_nome = calloc(1, sizeof(TelaNomeInfo));
    j->tela_nome->nChar =0;
}

void telanome_desenha(Jogo * j){
    TelaNomeInfo * tela = j->tela_nome;
    Rectangle textBox = {TELA_LARGURA/2.0f - 250, 300, 500, 50 };
    ClearBackground(BLACK);
    Vector2 pos = {.x=600, .y=200};
    texto_centralizado(j->fonte_menu, "Insira seu nome: ", pos, WHITE );
    DrawRectangleRec(textBox, LIGHTGRAY);

    texto_centralizado(j->fonte_menu, "Pressione ENTER para jogar!", (Vector2){.x=600,.y=500}, WHITE );
    DrawText(tela->nome, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
}

void telanome_entrada(Jogo *j){
    TelaNomeInfo * tela = j->tela_nome;
    int key = GetCharPressed();

    while (key > 0) {

        if ((key >= 32) && (key <= 125) && ( (tela->nChar)< TAM_MAX))
        {
            tela->nome[tela->nChar] = (char)key;
            tela->nome[(tela->nChar)+1] = '\0';
            (tela->nChar)++;
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)){
        tela->nChar--;
        if (tela->nChar < 0) tela->nChar = 0;
        tela->nome[tela->nChar] = '\0';
    }
    if (IsKeyPressed(KEY_ENTER)){
        strcpy(j->nome_jogador,tela->nome);
        jogo_troca_tela(j, TELA_JOGO);
    }
}

void telanome_logica(Jogo * j){

}

void telanome_termina(Jogo * j){
	free(j->tela_nome);
	j->tela_carrega = NULL;
}
