#include "board.hpp"
#include "movement.hpp"
#include "collision.hpp"
#include "victory.hpp"
#include "graphics.hpp"

int main() {
    Board board;
    initializeBoard(board);

    while (!isVictory(board)) {
        drawBoard(board);

        // Demander au joueur de déplacer un véhicule
        moveVehicle(board);

        // Vérifier s'il y a eu une collision
        if (isCollision(board)) {
            // Afficher un message d'erreur
            displayCollisionMessage();
            // Remettre le véhicule à sa position précédente
            undoLastMove(board);
        }
    }

    // Affichage du message de victoire
    displayVictoryMessage();

    return 0;
}
