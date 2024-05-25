
#include "Game.h"
#include <iostream>

Game::Game(int width, int height, int fps, std::string title)
        : padding(10.0f), screenHeight(height), screenWidth(width), player1({width / 3, height / 3}, {50, 50}, BLUE)
{
    assert(!GetWindowHandle()); // Check if window is already initialized
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
    initBall();
    DrawRectangle(10, 10, 980, 580, WHITE);
}

Game::~Game() noexcept
{
    assert(GetWindowHandle()); // Check if window is already closed
    CloseWindow();
}

bool Game::GameShouldClose() const
{
    return WindowShouldClose();
}

void Game::DrawBoard()
{
    ClearBackground(GREEN);

    float goalSpace = 50.0;
    float thickness = 5.0;
    DrawRectangleLinesEx({padding + goalSpace, padding, screenWidth - (padding + goalSpace) * 2, screenHeight - padding * 2}, thickness, WHITE);
    DrawLineEx(Vector2{screenWidth / 2, padding}, Vector2{screenWidth / 2, screenHeight - padding}, thickness, WHITE);
    //Draw Center Circle
    for (int i = 100; i < 105; i++)
    {
        DrawCircleLines(screenWidth / 2, screenHeight / 2, i, WHITE);
    }
    //Draw Goals
    DrawRectangleLinesEx({padding, 200, goalSpace + thickness, 200}, 5.0, BLUE);
    DrawRectangleLinesEx({screenWidth - padding - thickness - goalSpace, 200, goalSpace + thickness, 200}, 5.0, RED);
    //Draw Rectangles by Goals
    DrawRectangleLinesEx({padding + goalSpace, 150, 150, 300}, 5.0, WHITE);
    DrawRectangleLinesEx({screenWidth - padding - goalSpace - 150, 150, 150, 300}, 5.0, WHITE);
}

void Game::Tick()
{
    BeginDrawing();
    DrawBoard();
    Update();
    Draw();
    EndDrawing();
}

void Game::Update()
{
    if (player1.CheckCollisionWithBall(ball))
    {
        std::cout << "WORKS!";
    }
    player1.Update();
    ball.Update(player1);
}

void Game::Draw()
{
    player1.Draw();
    ball.Draw();
}

void Game::initPlayer()
{
    player1.setPlayer({screenWidth / 3, screenHeight / 3}, {50, 50}, BLUE);
}

void Game::initBall()
{
    ball.SetPosition({screenWidth / 2, screenHeight / 2});
    ball.SetRadius(10);
    ball.SetColor(BLACK);
}

