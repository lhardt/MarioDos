#ifndef TEXTURA_H
#define TEXTURA_H

typedef enum TexturaId {
	T_LOGO,
	E_MARIO1,
	E_MARIO2,
	D_MARIO2,
	E_TARTARUGA2,
	D_TARTARUGA2,
	TARTARUGA_V,
	E_CANO_S,
	D_CANO_S,
	E_CARANGUEJO_F,
	D_CARANGUEJO_F,
	E_CARANGUEJO_I,
	D_CARANGUEJO_I,
	CARANGUEJO_V,
	MOEDA1,
	MOEDA2,
	T_CORACAO,
	T_POW,
	E_CANO_I,
	D_CANO_I

	// TODO
	// mario parado, mario direita, mario caindo etc etc etc.
} TexturaId;

void textura_desenha(Jogo * j, TexturaId textura, Vector2 pos);

void texto_centralizado(Font font, char * text, Vector2 pos, Color cor);
Vector2 posfloat_para_tela(Vector2f v);

#endif /* TEXTURA_H */
