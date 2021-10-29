#ifndef TEXTURA_H
#define TEXTURA_H

typedef enum TexturaId {
	T_LOGO,
	T_MARIO1,
	// TODO
	// mario parado, mario direita, mario caindo etc etc etc.
} TexturaId;

void textura_desenha(Jogo * j, TexturaId textura, Vector2 pos);

void texto_centralizado(Font font, char * text, Vector2 pos, Color cor);
Vector2 posfloat_para_tela(Vector2f v);

#endif /* TEXTURA_H */
