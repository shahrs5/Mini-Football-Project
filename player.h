#pragma once

#include "raylib.h"
#include "rlgl.h"
#include "ball.h"


class Player
{
public:
    Player();
    Player(int type, Vector2 position, Color color, float Angle);

    void Draw();
    Vector2 Update();
    void Move(Vector2 direction);
    void setPlayer(Vector2 p, Vector2 s, Color c);
    Vector2 GetPosition() const;
    Vector2 GetSize() const;
    int getPlayerType();
//     Rectangle GetActiveSide() const;
//     bool CheckCollisionWithBall(Ball &ball);
    void SetPosition(Vector2 p);
    void SetColor(Color c);
    void RotatePlayer();
    void TogglePossession();
    bool CheckPossession() const;
    void Reset();

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
    bool Possession;
    int playerType;
};
