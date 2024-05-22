#include <raylib.h>
#include <iostream>
#include <string>

using namespace std;

Rectangle button1Rec = { 300 , 200, 200, 50 };
Rectangle button2Rec = { 300 , 300, 200, 50 };
Rectangle button3Rec = { 300 , 400, 200, 50 };
string generation = " ";

void drawMenu(){
    BeginDrawing();
        ClearBackground(BLACK);
        
        DrawText("Game Of Life", 400-MeasureText("Game Of Life",50)/2 ,30, 50, WHITE);
        DrawText("Red VS Blue", 400-MeasureText("Red VS Blue",30)/2 ,70, 30, WHITE);

        DrawRectangleGradientV(button1Rec.x, button1Rec.y, button1Rec.width, button1Rec.height, RED, BLUE);
        DrawText("Random Start", button1Rec.x + button1Rec.width / 2 - MeasureText("Random Start", 20) / 2, button1Rec.y + button1Rec.height / 2 - 10 , 20, WHITE);

        DrawRectangleGradientV(button2Rec.x, button2Rec.y, button2Rec.width, button2Rec.height, RED, BLUE);
        DrawText("Default Start", button2Rec.x + button2Rec.width / 2 - MeasureText("Default Start", 20) / 2, button2Rec.y + button2Rec.height / 2 - 10, 20, WHITE);

        DrawRectangleGradientV(button3Rec.x, button3Rec.y, button3Rec.width, button3Rec.height, RED, BLUE);
        DrawText("Load Start", button3Rec.x + button3Rec.width / 2 - MeasureText("Load Start", 20) / 2, button3Rec.y + button3Rec.height / 2 - 10 , 20, WHITE);
    EndDrawing();
}

void evenListeners(){
    if (CheckCollisionPointRec(GetMousePosition(), button1Rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        generation = "random";
    }
    if (CheckCollisionPointRec(GetMousePosition(), button2Rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        generation = "default";
    }
    if (CheckCollisionPointRec(GetMousePosition(), button3Rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        generation = "load";
    }
    drawMenu();
}