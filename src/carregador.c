#include "assert.h"

#include "jogo.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <raylib.h>


// out_str tem que ter no mínimo 17 bytes
bool scan_assinatura(FILE* out, char * out_str){
	struct tm assinado;
	int read = fscanf(out, "%02d/%02d/%02d, %02d:%02d\n",  &assinado.tm_mday,
				 		&assinado.tm_mon, &assinado.tm_year,
				 		&assinado.tm_hour, &assinado.tm_min);
	sprintf(out_str, "%02d/%02d/%02d, %02d:%02d", assinado.tm_mday,
				 		assinado.tm_mon, assinado.tm_year,
				 		assinado.tm_hour, assinado.tm_min);

	return (read == 5);
}

bool print_assinatura(FILE* out){
	ASSERT(out != NULL);
	time_t now_time = time(0);
	struct tm now_tm = *localtime(&now_time);
	fprintf(out, "%02d/%02d/%02d, %02d:%02d\n",  now_tm.tm_mday,
	 		now_tm.tm_mon, now_tm.tm_year - 100,
	 		now_tm.tm_hour, now_tm.tm_min);
	return true;
}

bool abre_arquivo(char * nomearq, FILE** out, bool is_leitura){
	ASSERT(nomearq != NULL && out != NULL);
	FILE * file = fopen(nomearq, is_leitura ? "rb" : "wb");

	char assinatura[20] = { 0 };

	bool success = file != NULL
			    &&(is_leitura ? scan_assinatura(file, assinatura) :  print_assinatura(file));

	if(success){
		printf("%s%s!\n", is_leitura?
							"Arquivo carregado com sucesso, de " :
							"Arquivo aberto para escrita com sucesso", assinatura);
	} else {
		printf("Erro na abertura do arquivo!\n");
	}

	*out = file;
	return success;
}

bool print_vector2(FILE * arq, Vector2 vec){
	ASSERT(arq != NULL);
	fprintf(arq, "Vec2[%f,%f]", vec.x, vec.y);
	return true;
}
bool scan_vector2(FILE * arq, Vector2 * vec){
	ASSERT(arq != NULL && vec != NULL);
	int num = fscanf(arq, "Vec2[%f,%f]", &vec->x, &vec->y);
	return (num == 2);
}

bool print_vector2f(FILE * arq, Vector2f vec){
	ASSERT(arq != NULL);
	fprintf(arq, "Vec2[%lf,%lf]", vec.x, vec.y);
	return true;
}
bool scan_vector2f(FILE * arq, Vector2f * vec){
	ASSERT(arq != NULL && vec != NULL);
	int num = fscanf(arq, "Vec2[%lf,%lf]", &vec->x, &vec->y);
	return (num == 2);
}\


bool print_moeda(FILE * arq, Moeda moeda){
	ASSERT(arq != NULL);
	fprintf(arq,"Moeda[");
	print_vector2f(arq, moeda.pos);
	print_vector2f(arq, moeda.vel);
	fprintf(arq,",%d]", moeda.coletada? 1:0);
}
bool scan_moeda(FILE * arq, Moeda * moeda){
	ASSERT(arq != NULL && moeda != NULL);
	int coletada = 0;

	bool success = (0 == fscanf(arq, "Moeda["))
				&& scan_vector2f(arq, &moeda->pos)
				&& scan_vector2f(arq, &moeda->vel)
				&& (1 == fscanf(arq, ",%d]", &coletada));
	moeda->coletada = (coletada) ? true : false;
	return success;
}
