#ifndef UNTITLED1_TIMER_H
#define UNTITLED1_TIMER_H

#include <raylib.h>

class Timer{
public:
    Timer(float startTime);
    void Update();
    void Draw(int posX, int posY) const;
    bool IsEnd() const;


private:
    float startTime;
    float currentTime;
};



#endif //UNTITLED1_TIMER_H
