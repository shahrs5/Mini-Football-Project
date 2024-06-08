#pragma once

#include "raylib.h"
#include "player.h"
#include "cstdio"

class Player; 

class Ball
{
public:
    Ball();
    Ball(Vector2 position, float radius, Color color);

    void Draw();
    void DrawEnd();
    void Update(Player player);
    void Updateposition(Player player);
    void Move(Vector2 direction);
    void SetPosition(Vector2 p);
    void SetColor(Color c);
    Vector2 GetPosition() const;
    float GetRadius() const;
    void SetRadius(float r);
    bool CheckCollisionCircleRec(Vector2 center, float radius, Player player);
    bool CheckGoal();
    void DrawScore();
    void Reset();


private:
    Vector2 position;
    Color color;
    float radius;
    int ball_speed_x;
    int ball_speed_y;
    int screenHeight;
    int screenWidth;
    float padding;
    Vector2 size;
    int score1;
    int score2;


};
