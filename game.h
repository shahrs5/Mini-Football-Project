#pragma once

#include <string>
#include <raylib.h>
#include <assert.h>
#include "player.h"
#include "ball.h"
#include "timer.h"

class Player;

class Game
{
public:
    Game(float width, float height, int fps, std::string title, float t);

    Game(const Game &other) = delete;
    Game &operator=(const Game &other) = delete;

    ~Game() noexcept;

    bool GameShouldClose() const;
    void DrawBoard();
    void Tick();
    void Reset();


private:
    float padding;
    float screenHeight;
    float screenWidth;
    Player player1;
    Player player2;
    Ball ball;
    Timer gametime;

    void Update();
    void Draw();
    void initPlayer();
    void initBall();

};
