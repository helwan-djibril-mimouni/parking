#include "board.hpp"
#include <iostream>

// Initialise le damier et les véhicules
void initializeBoard(Board& board) {
    // Initialise la taille du damier
    board.numRows = 6;
    board.numCols = 6;

    // Initialise la grille avec des cases vides
    board.grid.assign(board.numRows, std::vector<char>(board.numCols, '-'));

    // Ajoute les véhicules initiaux
    addVehicle(board, 2, 2, 3, VehicleType::BUS); // Bus jaune
    addVehicle(board, 0, 2, 2, VehicleType::CAR); // Voiture bleue
    addVehicle(board, 3, 0, 2, VehicleType::CAR); // Voiture bleue
    addVehicle(board, 4, 3, 3, VehicleType::BUS); // Bus bleu
}

// Ajoute un véhicule sur le damier
void addVehicle(Board& board, int row, int col, int size, VehicleType type) {
    Vehicle vehicle;
    vehicle.row = row;
    vehicle.col = col;
    vehicle.size = size;
    vehicle.type = type;
    board.vehicles.push_back(vehicle);

    // Met à jour la grille avec le nouveau véhicule
    for (int i = 0; i < size; ++i) {
        if (type == VehicleType::CAR) {
            board.grid[row][col + i] = 'C';
        } else {
            board.grid[row][col + i] = 'B';
        }
    }
}

// Affiche le damier avec les véhicules
void drawBoard(const Board& board) {
    // Affiche chaque ligne du damier
    for (int i = 0; i < board.numRows; ++i) {
        for (int j = 0; j < board.numCols; ++j) {
            std::cout << board.grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Vérifie si une case est en dehors du damier
bool isOutOfBounds(const Board& board, int row, int col) {
    return row < 0 || row >= board.numRows || col < 0 || col >= board.numCols;
}

// Vérifie si une case est occupée par un véhicule
bool isOccupied(const Board& board, int row, int col) {
    return board.grid[row][col] != '-';
}

// Vérifie si un véhicule peut être déplacé dans une direction donnée
bool canMoveVehicle(const Board& board, int index, int rowDelta, int colDelta) {
    const Vehicle& vehicle = board.vehicles[index];

    // Calcul de la nouvelle position du véhicule
    int newRow = vehicle.row + rowDelta;
    int newCol = vehicle.col + colDelta;

    // Vérification des limites du damier
    if (isOutOfBounds(board, newRow, newCol)) {
        return false;
    }

    // Vérification des collisions avec les autres véhicules
    for (int i = 0; i < vehicle.size; ++i) {
        if (isOccupied(board, newRow, newCol + i)) {
            return false;
        }
    }

    return true;
}

// Déplace un véhicule dans une direction donnée
void moveVehicle(Board& board, int index, int rowDelta, int colDelta) {
    Vehicle& vehicle = board.vehicles[index];

    // Efface l'ancienne position du véhicule
    for (int i = 0; i < vehicle.size; ++i) {
        board.grid[vehicle.row][vehicle.col + i] = '-';
    }

    // Met à jour la position du véhicule
    vehicle.row += rowDelta;
    vehicle.col += colDelta;

    // Affiche le véhicule à sa nouvelle position
    for (int i = 0; i < vehicle.size; ++i) {
        if (vehicle.type == VehicleType::CAR) {
            board.grid[vehicle.row][vehicle.col + i] = 'C';
        } else {
            board.grid[vehicle.row][vehicle.col + i] = 'B';
        }
    }
}

// Annule le dernier déplacement d'un véhicule
void undoLastMove(Board& board) {
    // Non implémenté dans cette version
    // Dans une version complète, cette fonction devrait garder une trace des mouvements
    // pour permettre d'annuler le dernier mouvement.
    // Ici, elle ne fait rien.
}
