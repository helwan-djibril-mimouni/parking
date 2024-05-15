#include "victory.hpp"
#include <iostream>

// Vérifie si la condition de victoire est remplie
bool isVictory(const Board& board) {
    // La condition de victoire est que le bus jaune se trouve sur la dernière ligne
    for (const auto& vehicle : board.vehicles) {
        if (vehicle.type == VehicleType::BUS && vehicle.row == board.numRows - 1) {
            return true;
        }
    }
    return false;
}

// Affiche un message de victoire
void displayVictoryMessage() {
    std::cout << "Félicitations ! Vous avez gagné." << std::endl;
}
