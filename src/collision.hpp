#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "board.hpp"

// Vérifie s'il y a eu une collision entre les véhicules
bool isCollision(const Board& board);

// Affiche un message en cas de collision
void displayCollisionMessage();

#endif // COLLISION_HPP
