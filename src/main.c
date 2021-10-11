#include <raylib.h>

#include "maths.h"

#define OPTIONS 7

void changeSelected(int upDown, int *options){
        int selecionada = -1;

        for (int x=0; x<OPTIONS && selecionada==-1;x++ ){
            if (options[x] !=0){
                selecionada = x;
            }
        }
        if(upDown==1){  //KEY_DOWN
            if (selecionada == OPTIONS-1){ // Se selecionada é a última opção
                options[0] = 1; // A primeira opção é agora a selecionada
            }
            else{
                options[selecionada+1] =1;
            }
        }
        else if (upDown ==-1){  //KEY_UP
            if (selecionada == 0){ // Se selecionada é a primeira opção
                options[OPTIONS-1] = 1; // A última opção é agora a selecionada
            }
            else{
                options[selecionada-1] =1;
            }
        }

         options[selecionada]=0;
    }

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    Color cores[] = {WHITE, BLUE};
    int options[10] = {1,0,0,0,0,0,0};

    // Font
    //Font fonte = LoadFont("./SuperMario256.ttf");



    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //Update
        if (IsKeyPressed(KEY_UP)){
            changeSelected(-1, options);
        }
        else if(IsKeyPressed(KEY_DOWN)){
            changeSelected(1, options);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            Vector2 pos;
            pos.x = 190;
            pos.y = 200;

            //DrawTextEx(fonte, "Novo jogo", pos, 20, 5, cores[options[0]]);
            DrawText("Continuar", 190, 230, 20, cores[options[1]]);
            DrawText("Carregar mapa", 190, 260, 20, cores[options[2]]);
            DrawText("Ranking", 190, 290, 20, cores[options[3]]);
            DrawText("Ajuda", 190, 320, 20, cores[options[4]]);
            DrawText("Sobre", 190,350, 20, cores[options[5]]);
            DrawText("Sair", 190, 380, 20, cores[options[6]]);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------


    return 0;
}
