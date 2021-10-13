/**
 * MarioDos.
 *   jogo.h - funções gerais para a divisão do jogo em telas.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Este arquivo contém funções do loop de jogo básico, bem como
 * a declaração destas funções para cada uma das telas.
 */
#ifndef JOGO_H
#define JOGO_H

#include "tipos.h"

/**
 * Formas que o jogo como um todo tem de responder a eventos.
 * Geralmente mais amplas do que a de cada tela porticular.
 * Ex: Se definirmos o atalho CTRL+Q para sair do jogo, esse
 * atalho pertencerá a jogo_entrada, e não a uma tela em específico.
 *
 * Ex: se a tela atual é TELA_MENU,
 * 		tela_inicia chamará telamenu_inicia.
 */
void jogo_inicia(Jogo * j);
void jogo_desenha(Jogo * j);
void jogo_entrada(Jogo * j);
void jogo_logica(Jogo * j);
void jogo_termina(Jogo * j);
void jogo_troca_tela(Jogo * j, Tela nova_tela);

/**
 * Funções que 'repassam' para a tela atual uma chamada.
 *
 * Ex: se a tela atual é TELA_MENU,
 * 		tela_inicia chamará telamenu_inicia.
 */
void tela_inicia(Jogo * j);
void tela_desenha(Jogo * j);
void tela_entrada(Jogo * j);
void tela_logica(Jogo * j);
void tela_termina(Jogo * j);

/**
 * Formas que o programa deve responder a um evento
 * a depender da tela em que está.
 *
 * Ex: telamenu_desenha usará informações do atributo j->tela_menu
 *      e a dsenhará.
 */
void telamenu_inicia(Jogo * j);
void telamenu_desenha(Jogo * j);
void telamenu_entrada(Jogo * j);
void telamenu_logica(Jogo * j);
void telamenu_termina(Jogo * j);

void telamenu_inicia(Jogo * j);
void telajogo_desenha(Jogo * j);
void telajogo_entrada(Jogo * j);
void telajogo_logica(Jogo * j);
void telajogo_termina(Jogo * j);

#endif /* JOGO_H */
