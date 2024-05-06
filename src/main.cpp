#include <cstdlib>
#include <ctime>
#include <raylib.h>

static void UpdateDrawFrame(int matrix[][22]);

void InitMatrix(int matrix[][22]){
    //0 = dead, 1 = red, 2 = blue
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 22; j++){
            if (i == 4 && j == 5){
                matrix[i][j] = 1;
            }
            else{
                matrix[i][j] = 0;
            }
        }
    }
}

void RandomMatrix(int matrix[][22]){
    //0 = dead, 1 = red, 2 = blue
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 22; j++){
            int randomNum = std::rand() / ((RAND_MAX + 1u) / 3);
            matrix[i][j] = randomNum;
        }
    }
}

int main()
{
    int matrix[32][22];
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib");

    RandomMatrix(matrix);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        UpdateDrawFrame(matrix);
    }
#endif

    CloseWindow();

    return 0;
}

static void UpdateDrawFrame(int matrix[][22])
{
    BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 22; j++){
                if (matrix[i][j] == 1){
                    DrawRectangle(1+(25*i), 1+(25*j), 23, 23, RED);
                }
                else if (matrix[i][j] == 2){
                    DrawRectangle(1+(25*i), 1+(25*j), 23, 23, BLUE);
                }
                else{
                    DrawRectangle(1+(25*i), 1+(25*j), 23, 23, WHITE);
                }
            }
        }

        DrawRectangle(25, 555, 100, 40, DARKGRAY);
        DrawRectangle(187, 555, 100, 40, DARKGRAY);
        DrawRectangle(350, 555, 100, 40, DARKGRAY);
        DrawRectangle(512, 555, 100, 40, DARKGRAY);
        DrawRectangle(675, 555, 100, 40, DARKGRAY);

    EndDrawing();
}
