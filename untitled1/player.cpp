#include "player.h"
#include <cmath>

Player::Player() : position({0.0f, 0.0f}), color(WHITE), size({0.0f, 0.0f}), screenHeight(600), screenWidth(1000), padding(10.0f), rotationAngle(0.0f), isRotating(false), ActiveSideWidth(10) {}

Player::Player(Vector2 position, Vector2 size, Color color)
        : position(position), size(size), color(color), screenHeight(600), screenWidth(1000), padding(10.0f), rotationAngle(0.0f), isRotating(false), ActiveSideWidth(10) {}

void Player::Draw() {
    rlPushMatrix();
    rlTranslatef(position.x + size.x / 2, position.y + size.y / 2, 0);
    if (isRotating)
        rlRotatef(rotationAngle, 0, 0, 1);
    rlTranslatef(-size.x / 2, -size.y / 2, 0);
    DrawRectangle(0, 0, size.x, size.y, color);
    DrawRectangle(size.x - ActiveSideWidth, 0, ActiveSideWidth, size.y, YELLOW);
    rlPopMatrix();
}

Vector2 Player::Update() {
    Vector2 direction = {0.0f, 0.0f};
    float moveSpeed = 5.0f;

    if (IsKeyDown(KEY_RIGHT) && (position.x + size.x) < screenWidth - padding)
        direction.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT) && (position.x) > padding)
        direction.x -= moveSpeed;
    if (IsKeyDown(KEY_UP) && (position.y) > padding)
        direction.y -= moveSpeed;
    if (IsKeyDown(KEY_DOWN) && (position.y + size.y) < screenHeight - padding)
        direction.y += moveSpeed;

    if (IsKeyDown(KEY_SPACE)) {
        isRotating = true;
        rotationAngle += 5.0f;
    }

    Move(direction);
    return position;
}

void Player::Move(Vector2 direction) {
    position.x += direction.x;
    position.y += direction.y;
}

void Player::setPlayer(Vector2 p, Vector2 s, Color c) {
    position = p;
    size = s;
    color = c;
}

Vector2 Player::GetPosition() const {
    return position;
}

Vector2 Player::GetSize() const {
    return size;
}

Rectangle Player::GetActiveSide() const {
    Vector2 center = {position.x + size.x / 2, position.y + size.y / 2};
    double RotationAngleRadians = rotationAngle * DEG2RAD;
    Vector2 activeSidePosition = {size.x / 2 - ActiveSideWidth / 2,-size.y / 2};
    Vector2 rotatedPos = {
            float(center.x + (activeSidePosition.x * cos(RotationAngleRadians) - activeSidePosition.y * sin(RotationAngleRadians))),
            float(center.y + (activeSidePosition.x * sin(RotationAngleRadians) + activeSidePosition.y * cos(RotationAngleRadians)))
    };

    Rectangle activeSide = {
            rotatedPos.x,
            rotatedPos.y,
            float(ActiveSideWidth),
            size.y
    };
    return activeSide;
}

bool Player::CheckCollisionWithBall(Ball &ball) {
    Rectangle activeSide = GetActiveSide();
    Vector2 ballCenter = ball.GetPosition();
    float ballRadius = ball.GetRadius();
    return CheckCollisionCircleRec(ballCenter, ballRadius, GetActiveSide());
}

void Player::SetPosition(Vector2 p) {
    position = p;
}

void Player::SetColor(Color c) {
    color = c;
}

void Player::RotatePlayer() {
    rlPushMatrix();
    rlTranslatef(position.x + size.x / 2, position.y + size.y / 2, 0);
    rlRotatef(45, 0, 0, 1);
    rlTranslatef(-position.x - size.x / 2, -position.y - size.y / 2, 0);
    rlPopMatrix();
}
