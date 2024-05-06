#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <raylib.h>

static void UpdateDrawFrame(int matrix[][22]);
void SaveMatrixToFile(int matrix[][22]);
void LoadMatrixFromFile(int matrix[][22]);

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

    // Load matrix from file
    LoadMatrixFromFile(matrix);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        UpdateDrawFrame(matrix);
    }
    
    SaveMatrixToFile(matrix);
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

void SaveMatrixToFile(int matrix[][22])
{
    std::ofstream outFile("matrix.txt");

    if (outFile.is_open())
    {
        for (int i = 0; i < 22; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                outFile << matrix[i][j] << " ";
            }
            outFile << std::endl;
        }
        outFile.close();
    }
}

void LoadMatrixFromFile(int matrix[][22])
{
    std::ifstream inFile("matrix.txt");

    if (inFile.is_open())
    {
        for (int i = 0; i < 32; i++)
        {
            for (int j = 0; j < 22; j++)
            {
                inFile >> matrix[i][j];
            }
        }
        inFile.close();
        std::cout << "Matrix loaded from file 'matrix.txt'" << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for reading. Initializing matrix..." << std::endl;
        InitMatrix(matrix); // If file doesn't exist, initialize matrix with default values
    }
}
