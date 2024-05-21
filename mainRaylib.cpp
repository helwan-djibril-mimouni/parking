#include "raylib.h"
#include "raylib.h"

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
}
Car;

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

    Car easyCars[] = {
        { true, 0, 2, 2, LoadTexture("sprites/cars/1x2_player_purple.png") },
        { true, 1, 3, 2, LoadTexture("sprites/cars/1x2_minicar_blue.png") },
        { false, 1, 4, 2, LoadTexture("sprites/cars/1x3_normal_green.png") },
        { true, 2, 5, 2, LoadTexture("sprites/cars/1x2_minicar_black.png") },
        { false, 3, 2, 3, LoadTexture("sprites/cars/1x3_truck_white.png") },
    };

    Car mediumCars[] = {
        { true, 2, 2, 2, LoadTexture("sprites/cars/1x2_player_purple.png") },
        { false, 2, 0, 2, LoadTexture("sprites/cars/1x3_sport_car_red.png") },
        { true, 3, 0, 2, LoadTexture("sprites/cars/1x3_cabrio_blue - Copie.png") },
        { false, 4, 1, 2, LoadTexture("sprites/cars/1x3_pickup_gray.png") },
        { false, 4, 3, 2, LoadTexture("sprites/cars/1x3_touringcar_dark.png") },
        { true, 1, 4, 3, LoadTexture("sprites/cars/1x4_truck_red - Copie.png") },
        { false, 1, 2, 2, LoadTexture("sprites/cars/2x1_minicar_yellow.png") },
        { true, 2, 3, 2, LoadTexture("sprites/cars/1x3_normal_green - Copie.png") }
    };

    Car hardCars[] = {        
        { true, 0, 2, 2, LoadTexture("sprites/cars/1x2_player_purple.png") },
        { false, 0, 4, 2, LoadTexture("sprites/cars/1x3_normal_green.png") },
        { false, 0, 5, 2, LoadTexture("sprites/cars/1x3_normal_white.png") },
        { false, 0, 6, 2, LoadTexture("sprites/cars/1x3_normal_blue.png") },
        { true, 0, 3, 3, LoadTexture("sprites/cars/1x4_truck_red - Copie.png") },
        { false, 2, 1, 2, LoadTexture("sprites/cars/1x3_cabrio_yellow.png") },
        { true, 4, 4, 2, LoadTexture("sprites/cars/1x2_minicar_blue.png") },
        { true, 4, 5, 2, LoadTexture("sprites/cars1x2_minicar_black.png") },
        { false, 1, 4, 3, LoadTexture("sprites/1x4_truck_green.png") }
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
    }

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(Car *cars, int numCars, Car **selectedCar) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Image parking = LoadImage("sprites/background/parking.png");
    Texture2D parking_texture = LoadTextureFromImage(parking);
    DrawTexture(parking_texture, 0, 0, WHITE);
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            DrawRectangleLines(i * cellSize, j * cellSize, cellSize, cellSize, LIGHTGRAY);
        }
    }

    // Draw cars
    for (int i = 0; i < numCars; i++) {
        Car car = cars[i];
        Rectangle dest = { car.x * cellSize, car.y * cellSize,
                           car.isHorizontal ? car.size * cellSize : cellSize,
                           car.isHorizontal ? cellSize : car.size * cellSize };
        DrawTexturePro(car.texture, (Rectangle){0, 0, car.texture.width, car.texture.height},
                       dest, (Vector2){0, 0}, 0.0f, WHITE);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        *selectedCar = SelectCar(cars, numCars, mousePosition);
    }
if (*selectedCar != NULL) {
    if (IsKeyPressed(KEY_RIGHT)) {
        if ((*selectedCar)->isHorizontal) {
            MoveCar(*selectedCar, 1, 0, cars, numCars);
        }
    }
    if (IsKeyPressed(KEY_LEFT)) {
        if ((*selectedCar)->isHorizontal) {
            MoveCar(*selectedCar, -1, 0, cars, numCars);
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        if (!(*selectedCar)->isHorizontal) {
            MoveCar(*selectedCar, 0, 1, cars, numCars);
        }
    }
    if (IsKeyPressed(KEY_UP)) {
        if (!(*selectedCar)->isHorizontal) {
            MoveCar(*selectedCar, 0, -1, cars, numCars);
        }
        }
    }
    EndDrawing();
}
Car* SelectCar(Car *cars, int numCars, Vector2 mousePosition) {
    for (int i = 0; i < numCars; i++) {
        Car car = cars[i];
        Rectangle carRect = { car.x * cellSize, car.y * cellSize,
                              car.isHorizontal ? car.size * cellSize : cellSize,
                              car.isHorizontal ? cellSize : car.size * cellSize };
        if (CheckCollisionPointRec(mousePosition, carRect)) {
            return &cars[i];
        }
    }
    return NULL;
}
void MoveCar(Car *car, int dx, int dy, Car *cars, int numCars) {
    int newX = car->x + dx;
    int newY = car->y + dy;
    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) return;
    if (!CheckCollision(car, newX, newY, cars, numCars)) {
        car->x = newX;
        car->y = newY;
        CheckWinCondition(cars, numCars);
    }
}
bool CheckCollision(Car *car, int newX, int newY, Car *cars, int numCars) {
    for (int i = 0; i < numCars; i++) {
        if (&cars[i] == car) continue;
        int otherX = cars[i].x;
        int otherY = cars[i].y;
        int otherWidth = cars[i].isHorizontal ? cars[i].size : 1;
        int otherHeight = cars[i].isHorizontal ? 1 : cars[i].size;
        Rectangle otherRect = { otherX * cellSize, otherY * cellSize, otherWidth * cellSize, otherHeight * cellSize };
        int carWidth = car->isHorizontal ? car->size : 1;
        int carHeight = car->isHorizontal ? 1 : car->size;
        Rectangle carRect = { newX * cellSize, newY * cellSize, carWidth * cellSize, carHeight * cellSize };
        if (CheckCollisionRecs(carRect, otherRect)) {
            return true;
        }
    }
    return false;
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
        }
        EndDrawing();
}
void CheckWinCondition(Car *cars, int numCars) {
    for (int i = 0; i < numCars; i++) {
        if (cars[i].x == 5 && cars[i].y == 2) {
            DrawWinScreen();
            return;
        }
    }
}
int DrawLevelSelection() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        int centerX = screenWidth / 2;
        int centerY = screenHeight / 2;
        int buttonWidth = 200;
        int buttonHeight = 50;
        int spacing = 20;
        Rectangle easyButtonRect = { centerX - buttonWidth / 2, centerY - (buttonHeight / 2 + buttonHeight + spacing), buttonWidth, buttonHeight };
        Rectangle mediumButtonRect = { centerX - buttonWidth / 2, centerY - buttonHeight / 2, buttonWidth, buttonHeight };
        Rectangle hardButtonRect = { centerX - buttonWidth / 2, centerY + (buttonHeight / 2 + spacing), buttonWidth, buttonHeight };
        Rectangle quitButtonRect = { centerX - buttonWidth / 2, centerY + (buttonHeight / 2 + spacing) + 100, buttonWidth, buttonHeight };
        DrawRectangleRec(easyButtonRect, LIGHTGRAY);
        DrawRectangleRec(mediumButtonRect, LIGHTGRAY);
        DrawRectangleRec(hardButtonRect, LIGHTGRAY);
        DrawRectangleRec(quitButtonRect, LIGHTGRAY);
        DrawText("Facile", easyButtonRect.x + 10, easyButtonRect.y + 10, 20, BLACK);
        DrawText("Moyen", mediumButtonRect.x + 10, mediumButtonRect.y + 10, 20, BLACK);
        DrawText("Difficile", hardButtonRect.x + 10, hardButtonRect.y + 10, 20, BLACK);
        DrawText("Quitter", quitButtonRect.x + 10, quitButtonRect.y + 10, 20, BLACK);
        if (CheckCollisionPointRec(GetMousePosition(), easyButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return 0;
        }
        if (CheckCollisionPointRec(GetMousePosition(), mediumButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return 1;
        }
        if (CheckCollisionPointRec(GetMousePosition(), hardButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return 2;
        }
        if (CheckCollisionPointRec(GetMousePosition(), quitButtonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            runing = false;
            CloseWindow();
            return -1;
        }
        EndDrawing();
    }
    return -1;
}