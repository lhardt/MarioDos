/**
 * MarioDos.
 *   carregador.h - Salva e Carrega o estado do Jogo.
 *
 * (C) 2021 Ana Laura e Léo Hardt.
 *
 * Quando o jogador sai, e quando o jogador quer continuar,
 * para não perder seu progresso, salvamos/carregamos o estado
 * de jogo de um arquivo.
 */
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "jogo.h"

bool scan_assinatura(FILE* out, char * out_str);
bool print_assinatura(FILE* out);

bool scan_vector2(FILE * arq, Vector2 * vec);
bool print_vector2(FILE * arq, Vector2 vec);

bool print_moeda(FILE * arq, Moeda moeda);
bool scan_moeda(FILE * arq, Moeda * moeda);

bool print_inimigo(FILE * arq, Inimigo inimigo);
bool scan_inimigo(FILE * arq, Inimigo * inimigo);

bool print_mario(FILE * arq, Mario mario);
bool scan_mario(FILE * arq, Mario * mario);

bool print_fase(FILE * arq, Fase fase);
bool scan_fase(FILE * arq, Fase * fase);

bool abre_arquivo(char * nomearq, FILE** out, bool is_leitura);
