#include "Game.hpp"
#include "Car.hpp"
void UpdateDrawFrame(Car *cars, int numCars, Car **selectedCar) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    Image parking = LoadImage("sprites/background/parking.png");
    Texture2D parking_texture = LoadTextureFromImage(parking);
    DrawTexture(parking_texture, 0, 0, WHITE);
    UnloadImage(parking);

    // Draw the grid
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

    // Check for car selection
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        *selectedCar = SelectCar(cars, numCars, mousePosition);
    }

    // Move selected car
    if (*selectedCar != NULL) {
        if (IsKeyPressed(KEY_RIGHT)) MoveCar(*selectedCar, 1, 0, cars, numCars);
        if (IsKeyPressed(KEY_LEFT)) MoveCar(*selectedCar, -1, 0, cars, numCars);
        if (IsKeyPressed(KEY_DOWN)) MoveCar(*selectedCar, 0, 1, cars, numCars);
        if (IsKeyPressed(KEY_UP)) MoveCar(*selectedCar, 0, -1, cars, numCars);
    }

    EndDrawing();
}

void CheckWinCondition(Car *cars, int numCars) {
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
    return false;}

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
