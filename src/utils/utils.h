#pragma once

#include <raylib.h>

class Timer {
    public:
    Timer(double _wait_time);
    void Start();
    void Stop();
    void Update(); //false if finished
    bool IsDone();
    double TimeRemaining();
    double TimeElapsed();


    private:

    double wait_time; //in seconds
    double elapsed_time;
    bool active;
    bool finished;
};