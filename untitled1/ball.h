#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "player.h"
class Player; // Forward declaration
class Ball
{
public:
    Ball();
    Ball(Vector2 position, float radius, Color color);

    void Draw();
    void Update(Player player);
    Vector2 Updateposition();
    void Move(Vector2 direction);
    void SetPosition(Vector2 p);
    void SetColor(Color c);
    Vector2 GetPosition() const;
    float GetRadius() const;
    void SetRadius(float r);
    bool CheckCollisionCircleRec(Vector2 center, float radius, Player player);

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
};

#endif // BALL_H
