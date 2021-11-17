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
			return (Rectangle){.x = 20, .y =  10, .width =200, .height=72};
		case E_MARIO1:
			return (Rectangle){.x =  3, .y = 603, .width = 16, .height=21};
		case E_MARIO2:
			return (Rectangle){.x = 53, .y = 603, .width = 16, .height=21};
		case D_MARIO2:
			return (Rectangle){.x = 53, .y = 632, .width = 16, .height=21};
        case E_TARTARUGA2:
            return (Rectangle){.x = 30, .y = 355, .width = 17, .height=13};
        case D_TARTARUGA2:
            return (Rectangle){.x = 30, .y = 335, .width = 17, .height=13};
        case E_CANO:
			return (Rectangle){.x = 51, .y = 246, .width = 48, .height=30};
		case D_CANO:
			return (Rectangle){.x = 51, .y = 203, .width = 48, .height=30};
		case E_CARANGUEJO:
			return (Rectangle){.x =  6, .y = 419, .width = 16, .height=16};
		case T_CORACAO:
			return (Rectangle){.x =  7, .y = 591, .width =  8, .height= 8};
		case T_POW:
			return (Rectangle){.x =133, .y = 243, .width = 16, .height=16};

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
	const double SCALE = 3.5;
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

	// Tranquilo remover. É útil para testar se o carregamento da textura ta alinhado corretamente.
	// DrawRectangleLines(rect_final.x, rect_final.y, rect_final.width, rect_final.height, GREEN);

	DrawTextureTiled(j->spritesheet, rect_textura, rect_final, (Vector2){.x=0,.y=0}, 0.0f, SCALE, WHITE);
}
