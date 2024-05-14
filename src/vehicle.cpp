#include <iostream>

using namespace std;

class Vehicle {
    public:
        int x;
        int y;

        Vehicle(int x, int y){
            this->x = x;
            this->y = y;
        }

        void moveUP(){
            y++;
        }

        void moveDOWN(){
            y--;
        }

        void moveLEFT(){
            x--;
        }

        void moveRIGHT(){
            x++;
        }

        void print(){
            cout << "Vehicle is at: " << x << ", " << y << endl;
        }

        ~Vehicle(){};
};