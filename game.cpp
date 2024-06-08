#include "iostream"
#include "Game.h"

Game::Game(float width, float height, int fps, std::string title, float t)
        : padding(10.0f), screenHeight(height), screenWidth(width), player1(1, {(width / 2) - 80, (height / 2) - 25}, BLUE, 0.0f), player2(2, {(width/2) + 30, (height/2) - 25}, RED, 0.0f), gametime(t) // Initialize gametime with 30 seconds
{
    assert(!GetWindowHandle()); // Check if window is already initialized
    SetTargetFPS(fps);
    InitWindow(width, height, title.c_str());
    initBall();
    // field
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
    // rectangular field
    DrawRectangleLinesEx({padding + goalSpace, padding, screenWidth - (padding + goalSpace) * 2, screenHeight - padding * 2}, thickness, WHITE);
    // center line
    DrawLineEx(Vector2{screenWidth / 2, padding}, Vector2{screenWidth / 2, screenHeight - padding}, thickness, WHITE);

    // Draw Center Circle
    for (int i = 100; i < 105; i++)
    {
        DrawCircleLines(screenWidth / 2, screenHeight / 2, i, WHITE);
    }

    // Draw Goals
    DrawRectangleLinesEx({padding, 200, goalSpace + thickness, 200}, 5.0, BLUE);
    DrawRectangleLinesEx({screenWidth - padding - thickness - goalSpace, 200, goalSpace + thickness, 200}, 5.0, RED);

    // Draw Rectangles by Goals
    DrawRectangleLinesEx({padding + goalSpace, 150, 150, 300}, 5.0, WHITE);
    DrawRectangleLinesEx({screenWidth - padding - goalSpace - 150, 150, 150, 300}, 5.0, WHITE);
    ball.DrawScore();
    if (!gametime.IsEnd()) {
        gametime.Draw(screenWidth/2 - 7, 12); // Draw the timer at position (10, 10)
    } else {
        DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 30) / 2, screenHeight / 2 - 10, 30, BLACK);
        ball.DrawEnd();
    }


}

void Game::Tick()
{
    BeginDrawing();
    ClearBackground(GREEN);
    DrawBoard();
    Update();
    Draw();
    gametime.Update(); // Update the timer
    EndDrawing();
}

void Game::Update()
{
    if(!gametime.IsEnd()){
        if(ball.CheckGoal()){

            player1.Reset();
            player2.Reset();
        }
        player2.Update();
        player1.Update();

        ball.Update(player1);
        ball.Update(player2);
    }

}

void Game::Draw()
{
    player1.Draw();
    player2.Draw();
    ball.Draw();
}

void Game::initBall()
{
    ball.SetPosition({screenWidth / 2, screenHeight / 2});
    ball.SetRadius(10);
    ball.SetColor(BLACK);
}

void Game::Reset(){
    std::cout<<"works";
    player1.Reset();
    player2.Reset();
}

