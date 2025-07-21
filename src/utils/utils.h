#pragma once

#include "../globals.h"
#include <vector>
#include <raylib.h>


class SignalObserver {

    public:
    SignalObserver();
    virtual void OnSignal(SIGNAL signal) = 0;

    private:

};

class SignalEmiter {
    public:
    SignalEmiter();
    void AddObserver(SignalObserver &_observer);
    virtual void EmitSignal(SIGNAL signal) = 0;

    std::vector<SignalObserver *> observers;

    private:

};

class Timer : public SignalEmiter{
    public:
    Timer(double _wait_time);
    void Start();
    void Stop();
    void Update(); //false if finished
    bool IsDone();
    double TimeRemaining();
    double TimeElapsed();
    double GetWaitTime();
    
    void EmitSignal(SIGNAL signal) override;

    private:

    double wait_time; //in seconds
    double elapsed_time;
    bool active;
    bool finished;
};