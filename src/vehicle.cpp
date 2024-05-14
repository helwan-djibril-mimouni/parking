#include <iostream>

using namespace std;

class Vehicle {
    public:
        int x_top;
        int y_left;
        int x_bottom;
        int y_right;

        Vehicle(int x_top, int x_botton ,int y_left, int y_right){
            this->x_top = x_top;
            this->x_bottom = x_bottom;
            this->y_left = y_left;
            this->y_right = y_right;
        }

        void moveUP(){
            y_left++;
            y_right++;
        }

        void moveDOWN(){
            y_left--;
            y_right--;
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