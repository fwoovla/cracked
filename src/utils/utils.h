#pragma once

#include <vector>
#include <raylib.h>
#include <cmath>
#include <functional>
//#include "../../global_def.h"

#define MAX_SIGNAL_CONNECTIONS 256


enum SIGNAL {
    END_GAME,
    TIMER_TIMEOUT,
    PLAY_PRESSED,
    SHOULD_DELETE,
    CAN_FIRE,
};

class Signal {
    public:
    std::vector<std::function<void()>> callbacks;
    void Connect(std::function<void()> const& callback);
    void EmitSignal();    
};


class Timer{
    public:
    Timer(double _wait_time, bool _autostart, bool _one_shot);
    void Start();
    void Stop();
    void Update(); //false if finished
    bool IsDone();
    double TimeRemaining();
    double TimeElapsed();
    double GetWaitTime();
    
    Signal timout;

    double wait_time; //in seconds
    private:
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
    float angle = atan2(dir.y, dir.x);
    return angle;
}

inline float wrapAngle(float a) {
    a = std::fmod(a + PI, 2*PI);
    if (a < 0) a += 2*PI;
    return a - PI;
}

inline float shortestAngleDiffRad(float from, float to) {
    return wrapAngle(to - from);
}

// dt = seconds since last frame, maxTurn = radians per second

 inline float rotateTowardsRad(float current, float target, float maxTurn, float dt) {
    float diff = shortestAngleDiffRad(current, target);
    float maxStep = maxTurn * dt;
    if (std::fabs(diff) <= 1e-4f) return target;
    if (std::fabs(diff) <= maxStep) return target;
    return current + (diff > 0 ? 1 : -1) * maxStep;
}
