#ifndef TEXTURA_H
#define TEXTURA_H

typedef enum TexturaId {
	T_LOGO,
	E_MARIO1,
	E_MARIO2,
	D_MARIO2,
	D_TARTARUGA2,
	E_TARTARUGA2,
	E_CANO,
	D_CANO,
	E_CARANGUEJO,
	T_CORACAO,
	T_POW,

	// TODO
	// mario parado, mario direita, mario caindo etc etc etc.
} TexturaId;

void textura_desenha(Jogo * j, TexturaId textura, Vector2 pos);

void texto_centralizado(Font font, char * text, Vector2 pos, Color cor);
Vector2 posfloat_para_tela(Vector2f v);

#endif /* TEXTURA_H */
