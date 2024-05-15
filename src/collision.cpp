#include "collision.hpp"
#include <iostream>

// Vérifie s'il y a eu une collision entre les véhicules
bool isCollision(const Board& board) {
    for (size_t i = 0; i < board.vehicles.size(); ++i) {
        const Vehicle& current = board.vehicles[i];
        for (size_t j = i + 1; j < board.vehicles.size(); ++j) {
            const Vehicle& other = board.vehicles[j];
            // Vérifie si les véhicules sont sur la même ligne ou colonne
            if (current.row == other.row && current.col + current.size > other.col && other.col + other.size > current.col) {
                return true;
            }
        }
    }
    return false;
}

// Affiche un message en cas de collision
void displayCollisionMessage() {
    std::cout << "Collision ! Déplacement impossible." << std::endl;
}
