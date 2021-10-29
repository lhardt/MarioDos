#include "jogo.h"

#include "textura.h"
#include "jogo.h"
#include "assert.h"

Vector2 posfloat_para_tela(Vector2f v){
	return (Vector2){.x = (int) (v.x * TILE_LARGURA), .y = (int) (v.y * TILE_ALTURA) };
}

// TODO nome melhor?
Rectangle get_spritesheet_pos(TexturaId textura){
	switch(textura){
		case T_LOGO:
			return (Rectangle){.x = 20, .y = 10, .width=200, .height=72};
		case T_MARIO1:
			return (Rectangle){.x = 0, .y = 600, .width = 20, .height=25};
			break;
		default:
			TODO();
	}
	ASSERT(false);
	return (Rectangle){.x=0, .y=0, .width=0, .height=0};
}

void texto_centralizado(Font font, char * text, Vector2 pos, Color cor){
	Vector2 text_measure = MeasureTextEx(font, text, 20,5);
	pos.x -= text_measure.x/2;
	DrawTextEx(font, text, pos, 20, 5, cor);
}


void textura_desenha(Jogo * j, TexturaId textura, Vector2 pos){
	const int SCALE = 3;
	// TODO: é mais útil pra gente usar x,y como coordenada
	// do canto superior-esq do objeto ou como o centro dele? acho que centro, porque na hora de verificar
	// se tal coisa encostou em tal acho mais fácil se basear no centro (?)
	Rectangle rect_textura = get_spritesheet_pos(textura);
	Rectangle rect_final = {.x = pos.x, .y = pos.y,
						    .width = SCALE * rect_textura.width,
							.height = SCALE * rect_textura.height
						};
	rect_final.x -= rect_final.width / 2;
	rect_final.y -= rect_final.height / 2;
	DrawTextureTiled(j->spritesheet, rect_textura, rect_final, (Vector2){.x=0,.y=0}, 0.0f, SCALE, WHITE);
}
