#include "ball.h"
#include "iostream"
#include "game.h"

Ball::Ball() : position({100.0f, 100.0f}), radius(15.0f), color(WHITE), ball_speed_x(0), ball_speed_y(0), screenHeight(600), screenWidth(1000), padding(10.0f), score1(0), score2(0) {}

Ball::Ball(Vector2 position, float radius, Color color)
        : position(position), radius(radius), color(color), ball_speed_x(0), ball_speed_y(0), screenHeight(600), screenWidth(1000), padding(10.0f), score1(0), score2(0){}

void Ball::Draw() {
    DrawCircle(position.x, position.y, radius, color);
}

void Ball::Update(Player player) {
    float x = player.GetPosition().x;
    float y = player.GetPosition().y;
    if (!CheckCollisionCircleRec(position, radius, player)) {
        position.x += ball_speed_x;
        position.y += ball_speed_y;
    }

    // ball bouncing back
    if (position.x + radius > 930 || position.x - radius < 70) {
        if(position.y + radius <= 200 || position.y + radius >= 400) {
            ball_speed_x *= -1;
        } else if(position.x + radius > 980 || position.x - radius < 20){
            ball_speed_x *= -1;
        }
    }

    if(position.y + radius > 580 || position.y - radius < 20){
        if (position.x + radius <= 930 || position.x - radius >= 20){
            ball_speed_y *= -1;
        } else if(position.y + radius > 400 || position.y - radius < 200){
            ball_speed_y *= -1;
        }
    }


    if (CheckCollisionCircleRec(position, radius, player)) {
        player.TogglePossession();
    }

    // ball kicking for player 1
    if (player.CheckPossession()) {
        Vector2 a = player.GetPosition();
        if (player.getPlayerType() == 1) {
            Updateposition(player);
            if (IsKeyDown(KEY_K)) {
                // kick straight
                if (a.x < position.x) {
                        position.x += 50;
                        ball_speed_x = 3;
                        ball_speed_y = 0;
                }

            }
            if (IsKeyDown(KEY_L)) {
                // kick right 45 degree
                if (a.x < position.x) {
                        position.x += 50;
                        position.y += 50;
                        ball_speed_x = 2;
                        ball_speed_y = 2;
                }
            }
            if (IsKeyDown(KEY_J)) {
                // kick left 45 degree
                if (a.x < position.x) {
                        position.x += 50;
                        position.y -= 50;
                        ball_speed_x = 2;
                        ball_speed_y = -2;

                }
            }
        } else if (player.getPlayerType() == 2) {  // kick the ball for player 2
            Updateposition(player);
            if ( IsKeyDown(KEY_G)) {
                // kick straight
                if (a.x >= position.x)
                        position.x -= 50;
                        ball_speed_x = -3;
                        ball_speed_y = 0;
                }

            }
            if (IsKeyDown(KEY_H)) {
                // kick right 45 degree
                if (a.x >= position.x) {
                        position.x -= 50;
                        position.y -= 50;
                        ball_speed_x = -2;
                        ball_speed_y = -2;
                }
            }
            if (IsKeyDown(KEY_F)) {
                // kick left 45 degree
                if (a.x >= position.x) {
                        position.x -= 50;
                        position.y += 50;
                        ball_speed_x = -2;
                        ball_speed_y = 2;

                }
            }
        }
    }

void Ball::Updateposition(Player player) {
    if(player.getPlayerType() == 1){
        SetPosition({player.GetPosition().x + player.GetSize().x, player.GetPosition().y + player.GetSize().y/2});
    } else if(player.getPlayerType() == 2){
        SetPosition({player.GetPosition().x , player.GetPosition().y + player.GetSize().y/2});
    }

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

bool Ball::CheckCollisionCircleRec(Vector2 center, float radius, Player player) {
    if (center.x + radius >= player.GetPosition().x && center.x - radius <= player.GetPosition().x + player.GetSize().x &&
        center.y + radius >= player.GetPosition().y && center.y - radius <= player.GetPosition().y + player.GetSize().y) {
        return true;
    }
    else {
        return false;
    }
}

void Ball::Reset(){
    ball_speed_x = 0;
    ball_speed_y = 0;
    SetPosition({500, 300});

}

bool Ball::CheckGoal() {
    if(position.x > 930 && position.y > 200 && position.y < 400 ){
        Reset();
        score1++;
        return true;
    }
    else if(position.x < 70 && position.y > 200 && position.y < 400){
        Reset();
        score2++;
        return true;

    }
    return false;
}

void Ball::DrawScore() {
    char s1[50];
    sprintf(s1, "%d", score1);
    char s2[50];
    sprintf(s2, "%d", score2);
    DrawText(s1, 10,  10, 30, BLUE);
    DrawText(s2, screenWidth - MeasureText(s2, 30) - 10,  10, 30, RED);
}

void Ball::DrawEnd() {
    if(score2 > score1){
        DrawText("Player 2 wins" , screenWidth / 2 - MeasureText("Player 2 wins", 30) / 2, screenHeight / 2 - 40, 30, BLACK);
    }
    else if(score1 > score2){
        DrawText("Player 1 wins" , screenWidth / 2 - MeasureText("Player 1 wins", 30) / 2, screenHeight / 2 - 40, 30, BLACK);
    }
    else{
        DrawText("Match Tie" , screenWidth / 2 - MeasureText("Game Tie", 30) / 2, screenHeight / 2 - 40, 30, BLACK);

    }
}

