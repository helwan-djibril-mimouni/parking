#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

// Définition des types de véhicules
enum class VehicleType { CAR, BUS };

// Structure représentant un véhicule sur le damier
struct Vehicle {
    int row; // Position de la première case du véhicule (ligne)
    int col; // Position de la première case du véhicule (colonne)
    int size; // Taille du véhicule (nombre de cases occupées)
    VehicleType type; // Type du véhicule (voiture ou bus)
};

// Structure représentant le damier
struct Board {
    std::vector<std::vector<char>> grid; // Matrice représentant le damier
    std::vector<Vehicle> vehicles; // Liste des véhicules sur le damier
    int numRows; // Nombre de lignes du damier
    int numCols; // Nombre de colonnes du damier
};

// Prototypes des fonctions
void initializeBoard(Board& board);
void drawBoard(const Board& board);
void addVehicle(Board& board, int row, int col, int size, VehicleType type);
bool isOutOfBounds(const Board& board, int row, int col);
bool isOccupied(const Board& board, int row, int col);
bool canMoveVehicle(const Board& board, int index, int rowDelta, int colDelta);
void moveVehicle(Board& board, int index, int rowDelta, int colDelta);
void undoLastMove(Board& board);

#endif // BOARD_HPP
