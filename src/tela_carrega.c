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

#define TAM_MAX 22

struct TelaCarregaInfo {
    char arquivo[TAM_MAX];
    int nChar;
};

void telacarrega_inicia(Jogo * j){
    j->tela_carrega = calloc(1, sizeof(TelaCarregaInfo));
    j->tela_carrega->nChar =0;
}

void telacarrega_desenha(Jogo * j){
    TelaCarregaInfo * tela = j->tela_carrega;
    Rectangle textBox = {TELA_LARGURA/2.0f - 250, 300, 500, 50 };
    ClearBackground(BLACK);
    Vector2 pos = {.x=600, .y=200};
    texto_centralizado(j->fonte_menu, "Insira o nome do arquivo: ", pos, WHITE );
    DrawRectangleRec(textBox, LIGHTGRAY);

    texto_centralizado(j->fonte_menu, "Pressione ENTER!", (Vector2){.x=600,.y=500}, WHITE );
    DrawText(tela->arquivo, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
}

void telacarrega_entrada(Jogo *j){
    TelaCarregaInfo * tela = j->tela_carrega;
    int key = GetCharPressed();

    while (key > 0) {

        if ((key >= 32) && (key <= 125) && ( (tela->nChar)< TAM_MAX))
        {
            tela->arquivo[tela->nChar] = (char)key;
            tela->arquivo[(tela->nChar)+1] = '\0'; // Add null terminator at the end of the string.
            (tela->nChar)++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE)){
        tela->nChar--;
        if (tela->nChar < 0) tela->nChar = 0;
        tela->arquivo[tela->nChar] = '\0';
    }
    if (IsKeyPressed(KEY_ENTER)){
        strcpy(j->nome_fase,tela->arquivo);
        jogo_troca_tela(j, TELA_JOGO);
    }
}

void telacarrega_logica(Jogo * j){

}

void telacarrega_termina(Jogo * j){
	free(j->tela_carrega);
	j->tela_carrega = NULL;
}
