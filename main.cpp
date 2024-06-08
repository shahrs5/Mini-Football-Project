#include "game.h"

int main(){
    const int screenWidth = 1000;
    const int screenHeight = 600;
    Game game(screenWidth, screenHeight, 60, "Soccer Game", 90);
    while (!game.GameShouldClose())
    {
        game.Tick();
    }


    return 0;
}