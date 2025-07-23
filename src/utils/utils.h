#pragma once

#include "../globals.h"
#include <vector>
#include <raylib.h>


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






