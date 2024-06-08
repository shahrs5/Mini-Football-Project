#include "timer.h"
#include <cstdio>

Timer::Timer(float startTime) {
    startTime = startTime;
    currentTime = startTime;
}

void Timer::Update() {
    if (currentTime > 0) {
        currentTime -= GetFrameTime();
    } else {
        currentTime = 0;
    }
}

void Timer::Draw(int posX, int posY) const {
    char temp[50]; // Create a buffer to hold the formatted string
    sprintf(temp, "%.0f", currentTime);
    DrawText(temp, posX, posY, 30, BLACK);

}
bool Timer::IsEnd() const {
    return currentTime <= 0;
}



