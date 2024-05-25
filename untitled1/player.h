#pragma once

#include "raylib.h"
#include "rlgl.h"
#include "ball.h"
class Ball; // Forward declaration
class Player
{
public:
    Player();
    Player(Vector2 position, Vector2 size, Color color);

    void Draw();
    Vector2 Update();
    void Move(Vector2 direction);
    void setPlayer(Vector2 p, Vector2 s, Color c);
    Vector2 GetPosition() const;
    Vector2 GetSize() const;
    Rectangle GetActiveSide() const;
    Rectangle GetPlayerBody();
    bool CheckCollisionWithBall(Ball &ball);
    void SetPosition(Vector2 p);
    void SetColor(Color c);
    void RotatePlayer();

private:
    Vector2 position;
    Color color;
    Vector2 size;
    int screenHeight;
    int screenWidth;
    float padding;
    float rotationAngle;
    bool isRotating;
    int ActiveSideWidth;
};
