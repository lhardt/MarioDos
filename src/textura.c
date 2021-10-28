#include "jogo.h"

#include "textura.h"
#include "jogo.h"
#include "assert.h"

// TODO nome melhor?
Rectangle get_spritesheet_pos(TexturaId textura){
	switch(textura){
		case T_LOGO:
			return (Rectangle){.x = 0, .y=0, .width=300, .height=100};
		default:
			TODO();
	}
	ASSERT(false);
	return (Rectangle){.x=0, .y=0, .width=0, .height=0};
}

void textura_desenha(Jogo * j, TexturaId textura, Vector2 pos){
	// TODO: é mais útil pra gente usar x,y como coordenada
	// do canto superior-esq do objeto ou como o centro dele? acho que centro, porque na hora de verificar
	// se tal coisa encostou em tal acho mais fácil se basear no centro (?)
	DrawTextureRec(j->spritesheet, get_spritesheet_pos(textura), pos, WHITE);
}
