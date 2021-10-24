#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>

// Funções de conveniência para erros de programação (principalmente 'chamou com parâmetros errados').
// Essas funções dão nome do arquivo e número da linha para ajudar.
// Talvez dê para fazer com que quando a gente tá compilando pra testes ela faça o teste invalidar.
// a TODO() é legal de usar quando tu cria uma função em branco que vá preencher mais tarde.
#define RAISE( m ) do{ fprintf(stderr, "Assertion Error (F: %s, L: %d, E: %s);\n", __FILE__, __LINE__, m); }while(0)
#define ASSERT( c ) do{if(!(c)){RAISE("Assertion " #c);}}while(0)
#define TODO( ) do{fprintf(stderr, "To Do! (F: %s, L: %d, f: %s);\n", __FILE__, __LINE__, __func__);}while(0)

#endif /* ASSERT_H */
