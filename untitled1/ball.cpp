#include "ball.h"

Ball::Ball() : position({100.0f, 100.0f}), radius(15.0f), color(WHITE), ball_speed_x(5), ball_speed_y(5), screenHeight(600), screenWidth(1000), padding(10.0f), size({0.0f, 0.0f}) {}

Ball::Ball(Vector2 position, float radius, Color color)
        : position(position), radius(radius), color(color), ball_speed_x(5), ball_speed_y(5), screenHeight(600), screenWidth(1000), padding(10.0f), size({0.0f, 0.0f}) {}

void Ball::Draw() {
    DrawCircle(position.x, position.y, radius, color);
}

void Ball::Update(Player player) {
    float x = player.GetPosition().x;
    float y = player.GetPosition().y;
    if (!CheckCollisionWithActiveSide(position, radius, player)) {
        position.x += ball_speed_x;
        position.y += ball_speed_y;
    }

    if (position.x + radius >= screenWidth || position.x - radius <= 0 ) {
        ball_speed_x *= -1;
    }

    if (position.y + radius >= screenHeight || position.y - radius <= 0 ) {
        ball_speed_y *= -1;
    }

    if (CheckCollisionWithActiveSide(position, radius, player)) {
        Updateposition();
        if (IsKeyDown(KEY_ENTER)) {
            Vector2 a = player.GetPosition();
            if(a.x > position.x)  position.x -= 50;
            if(a.x < position.x)  position.x += 50;
        }
    }
}

Vector2 Ball::Updateposition() {
    Vector2 direction = {0.0f, 0.0f};
    float moveSpeed = 5.0f;

    if (IsKeyDown(KEY_RIGHT) && (position.x + size.x) < screenWidth - padding) direction.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT) && (position.x) > padding) direction.x -= moveSpeed;
    if (IsKeyDown(KEY_UP) && (position.y) > padding) direction.y -= moveSpeed;
    if (IsKeyDown(KEY_DOWN) && (position.y + size.y) < screenHeight - padding) direction.y += moveSpeed;

    Move(direction);
    return position;
}

void Ball::Move(Vector2 direction) {
    position.x += direction.x;
    position.y += direction.y;
}

void Ball::SetPosition(Vector2 p) {
    position = p;
}

void Ball::SetColor(Color c) {
    color = c;
}

Vector2 Ball::GetPosition() const {
    return position;
}

float Ball::GetRadius() const {
    return radius;
}

void Ball::SetRadius(float r) {
    radius = r;
}

bool Ball::CheckCollisionWithActiveSide(Vector2 center, float radius, Player player) {
    Rectangle activeSide = player.GetActiveSide();
    return CheckCollisionCircleRec(center, radius, activeSide);
}

bool Ball::CheckCollisionWithPlayer(Vector2 center, float radius, Player player) {
    if (center.x + radius >= player.GetPosition().x && center.x - radius <= player.GetPosition().x + player.GetSize().x &&
        center.y + radius >= player.GetPosition().y && center.y - radius <= player.GetPosition().y + player.GetSize().y) {
        return true;
    }
    else {
        return false;
    }
}
