#include "board.cpp"
#include <raylib.h>

void DrawGame(const Board& board) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dessiner le damier
    DrawGrid(board.getRows(), board.getCols());

    // Dessiner les véhicules
    board.draw();

    EndDrawing();
}

void DrawGrid(int rows, int cols) {
    // Dessiner les lignes horizontales
    for (int i = 0; i <= rows; ++i) {
        DrawLine(0, i * 100, cols * 100, i * 100, LIGHTGRAY);
    }
    // Dessiner les lignes verticales
    for (int j = 0; j <= cols; ++j) {
        DrawLine(j * 100, 0, j * 100, rows * 100, LIGHTGRAY);
    }
}
