#pragma once

#include "../globals.h"
#include <vector>
#include <raylib.h>
#include <cmath>


class SignalObserver {

    public:
    virtual void OnSignal(SIGNAL signal) = 0;

    private:

};

class SignalEmiter {
    public:
    void ConnectSignalTo(SignalObserver *_observer);
    void EmitSignal(SIGNAL signal);

    std::vector< SignalObserver * > observers;

    private:

};

class Timer : public SignalEmiter{
    public:
    Timer(double _wait_time, bool _autostart, bool _one_shot);
    void Start();
    void Stop();
    void Update(); //false if finished
    bool IsDone();
    double TimeRemaining();
    double TimeElapsed();
    double GetWaitTime();

    private:
    double wait_time; //in seconds
    double elapsed_time;
    bool active;
    bool finished;
    bool one_shot;
    bool autostart;
};


inline Vector2 vClamp(Vector2 v, float maxLength) {
    float length = sqrtf(v.x * v.x + v.y * v.y);
    if (length > maxLength) {
        float scale = maxLength / length;
        v.x *= scale;
        v.y *= scale;
    }
    return v;
}

inline float GetAngleFromTo(Vector2 from, Vector2 to) {
    Vector2 dir = { to.x - from.x, to.y - from.y };
    float angle = atan2(dir.y, dir.x) * RAD2DEG;
    return angle;
}

