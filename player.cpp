#include "player.h"

Player::Player() : position({0.0f, 0.0f}),color(WHITE), size({0.0f, 0.0f}), screenHeight(600), screenWidth(1000), padding(10.0f), rotationAngle(0.0f), isRotating(false), ActiveSideWidth(10), Possession(false) {}

Player::Player(int type, Vector2 position, Color color, float Angle)
        : position(position), size({50, 50}), color(color), screenHeight(600), screenWidth(1000), padding(10.0f), rotationAngle(0.0f), isRotating(false), ActiveSideWidth(10), Possession(false), playerType(type) {
    if (playerType == 1) {
        rotationAngle = Angle;
    }
    if (playerType == 2) {
        rotationAngle = Angle;
    }
}

void Player::Draw() {
    rlPushMatrix();
    rlTranslatef(position.x + size.x / 2, position.y + size.y / 2, 0);
    if (isRotating)
        rlRotatef(rotationAngle, 0, 0, 1);
    rlTranslatef(-size.x / 2, -size.y / 2, 0);
    DrawRectangle(0, 0, size.x, size.y, color);
    if(playerType == 1){
        DrawRectangle(size.x - ActiveSideWidth, 0, ActiveSideWidth, size.y, YELLOW); // for player 1
    }
    else{
        DrawRectangle(0, 0, ActiveSideWidth, size.y, YELLOW);
    }
    rlPopMatrix();
}

Vector2 Player::Update() {
    Vector2 direction = {0.0f, 0.0f};
    float moveSpeed = 5.0f;

    if (IsKeyDown(KEY_RIGHT) && (position.x + size.x) < screenWidth - padding && playerType == 1)
        direction.x += moveSpeed;
    else if(IsKeyDown(KEY_D) && (position.x + size.x) < screenWidth - padding && playerType == 2)
        direction.x += moveSpeed;
    if (IsKeyDown(KEY_LEFT) && (position.x) > padding && playerType == 1)
        direction.x -= moveSpeed;
    else if(IsKeyDown(KEY_A) && (position.x) > padding && playerType == 2)
        direction.x -= moveSpeed;
    if (IsKeyDown(KEY_UP) && (position.y) > padding && playerType == 1)
        direction.y -= moveSpeed;
    else if(IsKeyDown(KEY_W) && (position.y) > padding && playerType == 2)
        direction.y -= moveSpeed;
    if (IsKeyDown(KEY_DOWN) && (position.y + size.y) < screenHeight - padding && playerType == 1)
        direction.y += moveSpeed;
    else if(IsKeyDown(KEY_S) && (position.y + size.y) < screenHeight - padding && playerType == 2)
        direction.y += moveSpeed;

    if (IsKeyDown(KEY_SPACE) && playerType == 1) {
        isRotating = true;
        rotationAngle += 5.0f;
    }
    else if(IsKeyDown(KEY_E) && playerType == 2) {
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

int Player::getPlayerType(){
    return playerType;
}

// to get the active side in order to shoot as per the rotation angle
//Rectangle Player::GetActiveSide() const {
//    Vector2 center = {position.x + size.x / 2, position.y + size.y / 2};
//    float RotationAngleRadians = rotationAngle * DEG2RAD;
//    Vector2 activeSidePosition = {size.x / 2 - ActiveSideWidth / 2,-size.y / 2};
//    Vector2 rotatedPos = {
//            center.x + (activeSidePosition.x * cos(RotationAngleRadians) - activeSidePosition.y * sin(RotationAngleRadians)),
//            center.y + (activeSidePosition.x * sin(RotationAngleRadians) + activeSidePosition.y * cos(RotationAngleRadians))
//    };
//    Rectangle activeSide = {
//            rotatedPos.x,
//            rotatedPos.y,
//            ActiveSideWidth,
//            size.y
//    };
//    return activeSide;
//}

//bool Player::CheckCollisionWithBall(Ball &ball) {
//    Rectangle activeSide = GetActiveSide();
//    Vector2 ballCenter = ball.GetPosition();
//    float ballRadius = ball.GetRadius();
//    return CheckCollisionCircleRec(ballCenter, ballRadius, GetActiveSide());
//}

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

void Player::TogglePossession() {
    Possession = !Possession;
}

bool Player::CheckPossession() const {
    return Possession;
}

void Player::Reset() {
    float w = screenWidth;
    float h = screenHeight;
    if(playerType == 1){
        SetPosition({(w / 2) - 80, (h / 2) - 25});
    }
    else{
        SetPosition({(w/2) + 30, (h/2) - 25});
    }
}
