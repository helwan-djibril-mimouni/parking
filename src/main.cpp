#include <cstdlib>
#include <ctime>
#include <raylib.h>

#include "function/menu.cpp"
#include "function/mainGame.cpp"

int main(){
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib");

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        if (generation == " "){
            evenListeners();
        }
        else if (!gameLaunch){
            LaunchGame(generation);
        }
        else{
            UpdateDrawFrame(matrix);
        }
    }
#endif

    CloseWindow();
    return 0;
}