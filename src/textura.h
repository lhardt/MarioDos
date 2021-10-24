#ifndef TEXTURA_H
#define TEXTURA_H

typedef enum TexturaId {
	T_LOGO,
	// TODO
	// mario parado, mario direita, mario caindo etc etc etc.
} TexturaId;

void textura_desenha(Jogo * j, TexturaId textura, Vector2 pos);

#endif /* TEXTURA_H */
