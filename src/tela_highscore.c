/**
 * MarioDos.
 *   tela_highscore.c - tela que mostra os jogadores com maior pontuação.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 */
#include "jogo.h"
#include "textura.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 22

struct TelaHighscoreInfo {
    Highscore * scores;
    int n_highscores;

};

void telahighscore_inicia(Jogo * j){
    j->tela_highscore = calloc(1, sizeof(TelaHighscoreInfo));
}

void telahighscore_desenha(Jogo * j){
    TelaHighscoreInfo * tela = j->tela_highscore;
    Rectangle textBox = {TELA_LARGURA/2.0f - 250, 300, 500, 50 };
    ClearBackground(BLACK);
    Vector2 pos = {.x=600, .y=200};
    texto_centralizado(j->fonte_menu, "Highscores: ", pos, WHITE );

    texto_centralizado(j->fonte_menu, "Pressione ENTER para voltar ao menu", (Vector2){.x=600,.y=500}, WHITE );

}

void telahighscore_entrada(Jogo *j){
    TelaHighscoreInfo * tela = j->tela_highscore;
    if (IsKeyPressed(KEY_ENTER)){
        jogo_troca_tela(j, TELA_MENU);
    }
}

void telahighscore_logica(Jogo * j){

}

void telahighscore_termina(Jogo * j){
	free(j->tela_highscore);
	j->tela_highscore = NULL;
}

/* Cria uma lista e salva essa lista em retptr. A lista tem o tamanho retptr_sz */
bool highscore_carrega(Highscore ** retptr, int * retptr_sz){
    ASSERT(retptr != NULL && retptr_sz != NULL);
    // Aloca mais um espaço porque facilita a criação de um novo item
    Highscore * list = calloc(11, sizeof(Highscore));
    if(! list ){
        printf("Erro de alocação!\n");
        return false;
    }

    FILE * scores_file = fopen("highscores.bin", "rb");
    if(scores_file == NULL){
        printf("Não foi possível abrir o arquivo");
        *retptr = list;
        *retptr_sz = 0;
        return true;
    }

    int i = 0; bool read = true;
    for(i = 0; read ; ++i){
        read = (4 == fscanf(scores_file, "[%c%c%c,%d]\n",
            & list[i].nome[0], & list[i].nome[1], & list[i].nome[2], &list[i].score
        ));
        if(i % 10 && i > 0){
            Highscore * newlist = realloc(list, (11 + i) * sizeof(Highscore));
            if(newlist == NULL){
                printf("Falta de memória!\n");
                fclose(scores_file);
                free(list);
                return false;
            }
            list = newlist;
        }
    }
    int n_lidos = i - 1;

    printf("Read %d scores.\n", n_lidos);
    fclose(scores_file);

    *retptr = list;
    *retptr_sz = n_lidos;
    return true;
}

bool highscore_salva(Jogo * j){
    Highscore novo = {.score = j->pontos};
    Highscore * lista_antiga;
    int n_lista;
    strncpy(novo.nome, j->nome_jogador, 1 + HIGHSCORE_NAME_SZ);
    bool loaded = highscore_carrega( &lista_antiga , &n_lista);

    if(!loaded){
        return highscore_grava_lista(&novo,1);
    }

    int i_subst = n_lista;
    for(int i = 0; i < n_lista; ++i){
        if(lista_antiga[i].score < novo.score){
            i_subst = i;
            break;
        }
    }

    // Não adianta substituir se não tem 'espaço'
    // Retorna true porque não foi nenhum erro.
    if(i_subst >= HIGHSCORES_NUM){
        free(lista_antiga); return true;
    }

    // Traz todos os menores que o novo para trás.
    // Ex: o 3ºagora vai ser 4º, o 4º, 5º, etc.
    for(int i = n_lista-1; i >= i_subst; --i){
        lista_antiga[i+1] = lista_antiga[i];
    }
    // Inseriu => nº de elementos total sobe.
    ++n_lista;

    lista_antiga[i_subst] = novo;

    bool sucesso = highscore_grava_lista(lista_antiga, n_lista);

    free(lista_antiga);
    return sucesso;
}

bool highscore_grava_lista(Highscore * list, int n_scores){
    printf("grava lista chamado com %d!\n", n_scores);
    ASSERT(list != NULL || n_scores <= 0);
    FILE * file = fopen("highscores.bin", "wb");
    if( file == NULL ) return false;
    for(int i = 0; i < n_scores && i < HIGHSCORES_NUM; ++i){
        fprintf(file, "[%c%c%c,%d]\n",
            list[i].nome[0], list[i].nome[1], list[i].nome[2], list[i].score
        );
    }

    fclose(file);
    return true;
}
