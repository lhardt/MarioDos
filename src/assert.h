#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>
#include <stdio.h>

// Funções de conveniência para erros de programação (principalmente 'chamou com parâmetros errados').
// Essas funções dão nome do arquivo e número da linha para ajudar.
#define RAISE( m ) do{ fprintf(stderr, "Assertion Error (F: %s, L: %d, E: %s);\n", __FILE__, __LINE__, m); }while(0)
#define ASSERT( c ) do{if(!(c)){RAISE("Assertion " #c);}}while(0)
#define TODO( ) do{fprintf(stderr, "To Do! (F: %s, L: %d, f: %s);\n", __FILE__, __LINE__, __func__);}while(0)

#endif /* ASSERT_H */
