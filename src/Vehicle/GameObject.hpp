class GameObject {
    public:
        int x_top;
        int y_left;
        int x_bottom;
        int y_right;

        GameObject(int x_top, int x_botton ,int y_left, int y_right): x_top(x_top), x_bottom(x_botton), y_left(y_left), y_right(y_right){}

        virtual void moveUP(){}

        virtual void moveDOWN(){}

        virtual void moveLEFT(){}

        virtual void moveRIGHT(){}

        virtual ~GameObject(){};
};