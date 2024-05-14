#include <iostream>

using namespace std;

class Vehicle {
    public:
        int x_top;
        int y_top;
        int x_bottom;
        int y_bottom;

        Vehicle(int x_top, int x_botton ,int y_top, int y_bottom){
            this->x_top = x_top;
            this->x_bottom = x_bottom;
            this->y_top = y_top;
            this->y_bottom = y_bottom;
        }

        void moveUP(){
            y_top++;
            y_bottom++;
        }

        void moveDOWN(){
            y_top--;
            y_bottom--;
        }

        void moveLEFT(){
            x_top--;
            x_bottom--;
        }

        void moveRIGHT(){
            x_top++;
            x_bottom++;
        }
        
        ~Vehicle(){};
};