#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <raylib.h>

#include "vehicle.cpp"
#include "board.cpp"
#include "game.cpp"
#include "graphics.cpp"
#include <raylib.h>

int main() {
    // Initialisation du jeu
    InitWindow(800, 600, "Parking Game");
    SetTargetFPS(60);

    // Initialisation du damier et des véhicules
    Board board(6, 6);
    // Initialiser les véhicules sur le damier
    InitializeVehicles(board);

    while (!WindowShouldClose()) {
        // Mettre à jour et afficher le jeu
        UpdateGame(board);
        DrawGame(board);
    }

    CloseWindow();
    return 0;
}
