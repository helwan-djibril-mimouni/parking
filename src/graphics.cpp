#include "graphics.hpp"

// Initialisation de la fenêtre graphique
void initGraphics(int screenWidth, int screenHeight, const char* title) {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
}

// Dessine le damier et les véhicules
void drawBoard(const Board& board) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Dessine chaque case du damier
    for (int i = 0; i < board.numRows; ++i) {
        for (int j = 0; j < board.numCols; ++j) {
            Rectangle rec = { static_cast<float>(j * 100), static_cast<float>(i * 100), 100.0f, 100.0f };
            if (board.grid[i][j] == 'C') {
                DrawRectangleRec(rec, BLUE);
            } else if (board.grid[i][j] == 'B') {
                DrawRectangleRec(rec, DARKBLUE);
            } else {
                DrawRectangleRec(rec, LIGHTGRAY);
            }
        }
    }

    EndDrawing();
}

// Ferme la fenêtre graphique
void closeGraphics() {
    CloseWindow();
}
