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
}

bool print_moeda(FILE * arq, Moeda moeda){
	ASSERT(arq != NULL);
	fprintf(arq,"Moeda[");
	print_vector2f(arq, moeda.pos);
	print_vector2f(arq, moeda.vel);
	fprintf(arq,",%d]", moeda.coletada? 1:0);

	return true;
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

bool print_inimigo(FILE * arq, Inimigo inimigo){
	ASSERT(arq != NULL);

	fprintf(arq, "Inimigo[%d,%d,", inimigo.tipo, inimigo.vivo ? 1:0);
	print_vector2f(arq, inimigo.pos);
	print_vector2f(arq, inimigo.vel);
	fprintf(arq, ",%d]", (int)inimigo.vulnerabilidade);

	return true;
}

bool scan_inimigo(FILE * arq, Inimigo * inimigo){
	ASSERT(arq != NULL);

	int tmpvivo, tmpvul, tmptipo;
	bool result = fscanf(arq, "Inimigo[%d,%d,]", &tmptipo, &tmpvivo)
			   && scan_vector2f(arq, &inimigo->pos)
			   && scan_vector2f(arq, &inimigo->vel)
			   && fscanf(arq,",%d]", &tmpvul);

	inimigo->vivo = (tmpvivo == 1);
	inimigo->tipo = tmptipo;
	inimigo->vulnerabilidade = tmpvul;

	return result;
}

bool print_mario(FILE * arq, Mario mario){
	ASSERT(arq != NULL);

	fprintf(arq,"Mario[");
	print_vector2f(arq,mario.pos);
	print_vector2f(arq,mario.vel);
	fprintf(arq,",%d,%d]", mario.score, mario.vidas);

	return true;
}
bool scan_mario(FILE * arq, Mario * mario){
	ASSERT(arq != NULL && mario != NULL);
	bool success;

	success = (0 == fscanf(arq, "Mario["))
		   && scan_vector2f(arq, &mario->pos)
		   && scan_vector2f(arq, &mario->vel)
		   && (2 == fscanf(arq, ",%d,%d]", &mario->score, &mario->vidas));
	return success;
}

bool print_fase(FILE * arq, Fase fase){
	ASSERT(arq != NULL);

	fprintf(arq,"Fase[%d,%d,%d", fase.n_mapa, fase.n_inimigos, fase.n_moedas);
	fprintf(arq, ",%d,%d,%d\n", fase.n_tartarugas, fase.n_caranguejos, fase.delay);

	print_mario(arq, fase.mario);

	fprintf(arq,"\n");
	fprintf(arq, "MOEDAS[");
	for(int i = 0; i < fase.n_moedas; ++i){
			fprintf(arq, "\n\t");
			print_moeda(arq, fase.moedas[i]);
	}
	fprintf(arq, "\n]\n");

	fprintf(arq,"INIMIGOS[");
	for(int i = 0; i < fase.n_inimigos; ++i){
			fprintf(arq,"\n\t");
			print_inimigo(arq, fase.inimigos[i]);
	}
	fprintf(arq,"\n]\n");


	for (int i_linha=0; i_linha < FASE_ALTURA; ++i_linha){
		for(int i_char = 0; i_char < FASE_LARGURA; ++i_char ){
			fputc(fase.mapa[i_linha][i_char], arq);
		}
	}
	fprintf(arq, "]\n");
	return true;
}
bool scan_fase(FILE * arq, Fase * fase){
	ASSERT(arq != NULL && fase != NULL);

	bool success = true;

	success &=
			(3 == fscanf(arq,"Fase[%d,%d,%d", &fase->n_mapa, &fase->n_inimigos, &fase->n_moedas))
		&&  (3 == fscanf(arq, ",%d,%d,%d\n", &fase->n_tartarugas, &fase->n_caranguejos, &fase->delay))
		&&  scan_mario(arq, &fase->mario)
		&&  (0 == fscanf(arq,"\n"))
		&&  (0 == fscanf(arq, "MOEDAS["));

	for(int i = 0; success && i < fase->n_moedas; ++i){
		success &= (0 == fscanf(arq, "\n\t"));
		success &= scan_moeda(arq, &fase->moedas[i]);
	}


	success &= (0 == fscanf(arq, "\n]\n"))
		    && (0 == fscanf(arq,"INIMIGOS["));


	for(int i = 0; success && i < fase->n_inimigos; ++i){
		success &= (0 == fscanf(arq, "\n\t"));
		success &= scan_inimigo(arq, &fase->inimigos[i]);
	}
	success &= (0 == fscanf(arq,"\n]\n"));

	for (int i_linha=0; i_linha < FASE_ALTURA; ++i_linha){
		for(int i_char = 0; i_char < FASE_LARGURA; ++i_char ){
			fase->mapa[i_linha][i_char] = fgetc(arq);
		}
	}
	success &= (0 == fscanf(arq, "]\n"));

	return success;
}
