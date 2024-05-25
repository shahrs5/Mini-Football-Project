#pragma once

#include <string>
#include <raylib.h>
#include <assert.h>
#include "player.h"
#include "ball.h"

class Game
{
public:
    Game(int width, int height, int fps, std::string title);

    Game(const Game &other) = delete;

    Game &operator=(const Game &other) = delete;

    ~Game() noexcept;

    bool GameShouldClose() const;

    void DrawBoard();

    void Tick();

private:
    float padding;
    float screenHeight;
    float screenWidth;
    Player player1;
    Ball ball;

    void Update();

    void Draw();

    void initPlayer();

    void initBall();
};
