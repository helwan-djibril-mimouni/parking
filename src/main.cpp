#include "raylib.h"
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 450;
const int cellSize = 10;
const int gridWidth = screenWidth / cellSize;
const int gridHeight = screenHeight / cellSize;

bool grid[gridWidth][gridHeight];
bool nextGrid[gridWidth][gridHeight];

void InitGrid() {
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = false;
            nextGrid[x][y] = false;
        }
    }
}

void UpdateGrid() {
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            int neighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (!(i == 0 && j == 0)) {
                        int nx = (x + i + gridWidth) % gridWidth;
                        int ny = (y + j + gridHeight) % gridHeight;
                        if (grid[nx][ny]) {
                            ++neighbors;
                        }
                    }
                }
            }
            if (grid[x][y]) {
                if (neighbors < 2 || neighbors > 3) {
                    nextGrid[x][y] = false;
                } else {
                    nextGrid[x][y] = true;
                }
            } else {
                if (neighbors == 3) {
                    nextGrid[x][y] = true;
                } else {
                    nextGrid[x][y] = false;
                }
            }
        }
    }
    // Copy nextGrid to grid
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = nextGrid[x][y];
        }
    }
}

void DrawGrid() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y]) {
                DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, BLACK);
            }
        }
    }
    EndDrawing();
}

int main() {
    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetWindowPosition((GetScreenWidth() - screenWidth) / 2, (GetScreenHeight() - screenHeight) / 2);
    SetTargetFPS(10);

    InitGrid();

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int x = GetMouseX() / cellSize;
            int y = GetMouseY() / cellSize;
            grid[x][y] = !grid[x][y];
        }
        
        UpdateGrid();
        DrawGrid();
    }

    CloseWindow();
    return 0;
}
