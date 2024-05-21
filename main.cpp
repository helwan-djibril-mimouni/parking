#include "raylib.h"
#include "Game.hpp"
#include "Car.hpp"
#include <stdio.h>
#include <stdlib.h>
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
const int screenWidth = 600;
const int screenHeight = 600;
const int cellSize = 100;
const int gridSize = 6;
typedef struct Car {
    bool isHorizontal;
    int x;
    int y;
    int size;
    Texture2D texture;
} Car;
void UpdateDrawFrame(Car *cars, int numCars, Car **selectedCar);
Car* SelectCar(Car *cars, int numCars, Vector2 mousePosition);
void MoveCar(Car *car, int dx, int dy, Car *cars, int numCars);
bool CheckCollision(Car *car, int newX, int newY, Car *cars, int numCars);
void CheckWinCondition(Car *cars, int numCars);
int DrawLevelSelection();
bool runing = true;
bool win = false;
int main() {
    InitWindow(screenWidth, screenHeight, "Rush Hour");
    SetTargetFPS(60);

    // Chargement des textures pour toutes les voitures
    Texture2D carTextures[] = {
        LoadTexture("sprites/cars/2x1_player_purple.png"),
        LoadTexture("sprites/cars/1x2_minicar_black.png"),
        LoadTexture("sprites/cars/2x1_minicar_yellow.png"),
        LoadTexture("sprites/cars/1x2_minicar_yellow.png"),
        LoadTexture("sprites/cars/2x1_minicar_blue.png"),
        LoadTexture("sprites/cars/1x2_pcar.png")
    };

    Car easyCars[] = {
        { true, 0, 2, 2, LoadTexture("sprites/cars/1x2_player_purple.png") },
        { true, 1, 3, 2, LoadTexture("sprites/cars/1x2_minicar_blue.png") },
        { false, 1, 4, 2, LoadTexture("sprites/cars/1x3_normal_green.png") },
        { true, 2, 5, 2, LoadTexture("sprites/cars/1x2_minicar_black.png") },
        { false, 3, 2, 3, LoadTexture("sprites/cars/1x3_truck_white.png") },
    };

    Car mediumCars[] = {
        { false, 0, 2, 2, carTextures[0] },
        { true, 2, 0, 2, carTextures[1] },
        { false, 3, 1, 2, carTextures[2] },
        { true, 4, 2, 2, carTextures[3] },
        { false, 1, 3, 2, carTextures[4] },
        { false, 0, 4, 2, carTextures[5] }
    };

    Car hardCars[] = {
        { false, 0, 2, 2, LoadTexture("sprites/cars/2x1_player_purple.png") },
        { false, 2, 1, 2, LoadTexture("sprites/cars/1x2_minicar_black.png") },
        { true, 0, 3, 3, LoadTexture("sprites/cars/?.png") },
        { false, 0, 4, 2, LoadTexture("sprites/cars/1x3_normal_green.png") },
        { false, 1, 4, 2, LoadTexture("sprites/cars/1x3_truck_white.png") },
        { false, 2, 4, 2, LoadTexture("sprites/cars/?.png") },
        { true, 4, 4, 2, LoadTexture("sprites/cars/2x1_minicar_yellow.png") },
        { true, 4, 5, 2, LoadTexture("sprites/cars/?.png") },
        { false, 4, 1, 3, LoadTexture("sprites/cars/?.png") },
        { true, 5, 2, 2, LoadTexture("sprites/cars/?.png") }
    };
    while(runing && !WindowShouldClose()){
        Car *cars;
        int numCars;

        int level = DrawLevelSelection();
        if (level == 0) {
            cars = easyCars;
            numCars = sizeof(easyCars) / sizeof(easyCars[0]);
        } else if (level == 1) {
            cars = mediumCars;
            numCars = sizeof(mediumCars) / sizeof(mediumCars[0]);
        } else {
            cars = hardCars;
            numCars = sizeof(hardCars) / sizeof(hardCars[0]);
        }

        Car *selectedCar = NULL;

        while (!WindowShouldClose()) {
            UpdateDrawFrame(cars, numCars, &selectedCar);
            if (win == true) break;
        }
        win = false;

        for (int i = 0; i < sizeof(carTextures) / sizeof(carTextures[0]); i++) {
            UnloadTexture(carTextures[i]);
        }
    }
    CloseWindow();
    return 0;
}
void DrawWinScreen() {
        BeginDrawing();
        ClearBackground(WHITE);
        win = true;

        DrawText("YOU WIN!", screenWidth / 2 - MeasureText("YOU WIN!", 40) / 2, screenHeight / 2 - 20, 40, BLACK);

        Rectangle backButtonRect = { screenWidth / 2 - 100, screenHeight / 2 + 20, 200, 50 };
        DrawRectangleRec(backButtonRect, LIGHTGRAY);
        DrawText("Retour", backButtonRect.x + 40, backButtonRect.y + 10, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), backButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return;
        EndDrawing();
    }
}