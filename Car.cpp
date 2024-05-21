#include "Car.hpp"

Car* SelectCar(Car *cars, int numCars, Vector2 mousePosition) {
    for (int i = 0; i < numCars; i++) {
        Car car = cars[i];
        Rectangle carRect = { car.x * cellSize, car.y * cellSize,
                              car.isHorizontal ? car.size * cellSize : cellSize,
                              car.isHorizontal ? cellSize : car.size * cellSize };
        if (CheckCollisionPointRec(mousePosition, carRect)) {
            return &cars[i];
        }
    }
    return NULL;
    
}

void MoveCar(Car *car, int dx, int dy, Car *cars, int numCars) {
    int newX = car->x + dx;
    int newY = car->y + dy;

    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) return;

    if (!CheckCollision(car, newX, newY, cars, numCars)) {
        car->x = newX;
        car->y = newY;
        CheckWinCondition(cars, numCars);
    }
}

bool CheckCollision(Car *car, int newX, int newY, Car *cars, int numCars) {
    for (int i = 0; i < numCars; i++) {
        if (&cars[i] == car) continue;

        int otherX = cars[i].x;
        int otherY = cars[i].y;
        int otherWidth = cars[i].isHorizontal ? cars[i].size : 1;
        int otherHeight = cars[i].isHorizontal ? 1 : cars[i].size;

        Rectangle otherRect = { otherX * cellSize, otherY * cellSize, otherWidth * cellSize, otherHeight * cellSize };

        int carWidth = car->isHorizontal ? car->size : 1;
        int carHeight = car->isHorizontal ? 1 : car->size;

        Rectangle carRect = { newX * cellSize, newY * cellSize, carWidth * cellSize, carHeight * cellSize };

        if (CheckCollisionRecs(carRect, otherRect)) {
            return true;
        }
    }
    return false;
    
}
