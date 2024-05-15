#include <raylib.h>

class Vehicle {
private:
    Vector2 position;
    bool isHorizontal;
    int length;
    Texture2D sprite;

public:
    Vehicle(Vector2 pos, bool horizontal, int len, Texture2D tex) : position(pos), isHorizontal(horizontal), length(len), sprite(tex) {}

    Vector2 getPosition() const { return position; }
    bool isHorizontal() const { return isHorizontal; }
    int getLength() const { return length; }
    Rectangle getBounds() const {
        return {position.x, position.y, isHorizontal ? length * sprite.width : sprite.width, isHorizontal ? sprite.height : length * sprite.height};
    }
    
    void move(int deltaX, int deltaY) {
        position.x += deltaX;
        position.y += deltaY;
    }

    void draw() {
        DrawTexture(sprite, position.x, position.y, WHITE);
    }
};
