#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "board.hpp"
#include "raylib.h"

// Initialisation de la fenêtre graphique
void initGraphics(int screenWidth, int screenHeight, const char* title);

// Dessine le damier et les véhicules
void drawBoard(const Board& board);

// Ferme la fenêtre graphique
void closeGraphics();

#endif // GRAPHICS_HPP
