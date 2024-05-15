#include "movement.hpp"
#include <iostream>

// Demande au joueur de choisir un véhicule à déplacer et une direction
void moveVehicle(Board& board) {
    int index;
    char direction;

    // Affiche les instructions pour le joueur
    std::cout << "Choisissez le véhicule à déplacer (0 pour le premier, 1 pour le deuxième, etc.) : ";
    std::cin >> index;

    // Vérifie si l'index est valide
    if (index < 0 || index >= static_cast<int>(board.vehicles.size())) {
        std::cout << "Index invalide !" << std::endl;
        return;
    }

    // Affiche les instructions pour choisir la direction
    std::cout << "Choisissez la direction (g pour gauche, d pour droite, b pour bas, h pour haut) : ";
    std::cin >> direction;

    int rowDelta = 0;
    int colDelta = 0;

    // Convertit la direction en deltas de déplacement
    switch (direction) {
        case 'g':
            colDelta = -1;
            break;
        case 'd':
            colDelta = 1;
            break;
        case 'b':
            rowDelta = 1;
            break;
        case 'h':
            rowDelta = -1;
            break;
        default:
            std::cout << "Direction invalide !" << std::endl;
            return;
    }

    // Vérifie si le déplacement est possible
    if (!canMoveVehicle(board, index, rowDelta, colDelta)) {
        std::cout << "Déplacement impossible !" << std::endl;
        return;
    }

    // Effectue le déplacement
    moveVehicle(board, index, rowDelta, colDelta);
}
