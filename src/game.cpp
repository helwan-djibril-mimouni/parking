#include "board.cpp"

bool checkMoveValidity(const Board& board, const Vehicle& vehicle, int deltaX, int deltaY) {
    // Vérifier si le mouvement est valide en fonction de la position et de l'orientation du véhicule
    Vector2 newPos = {vehicle.getPosition().x + deltaX, vehicle.getPosition().y + deltaY};

    // Vérifier les limites du damier
    if (newPos.x < 0 || newPos.x >= board.getCols() * vehicle.getBounds().width ||
        newPos.y < 0 || newPos.y >= board.getRows() * vehicle.getBounds().height) {
        return false;
    }

    // Vérifier si la nouvelle position est vide
    if (!board.isPositionEmpty(newPos)) {
        return false;
    }

    // Vérifier les mouvements horizontaux
    if (vehicle.isHorizontal()) {
        if (deltaY != 0) {
            return false;
        }
    }
    // Vérifier les mouvements verticaux
    else {
        if (deltaX != 0) {
            return false;
        }
    }

    return true;
}

bool checkVictory(const Board& board) {
    // Vérifier si la condition de victoire est remplie (la voiture jaune est arrivée de l'autre côté)
    for (int i = 0; i < board.getCols(); ++i) {
        if (!board.isPositionEmpty({i * 100, 0})) {
            return true;
        }
    }
    return false;
}
