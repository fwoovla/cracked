#include "utils.h"

Timer::Timer(double _wait_time) {
    wait_time = _wait_time;
    active = false;
    finished = false;
    elapsed_time = 0.0;
    bool autostart = true;

    if(autostart) {
        Start();
    }
}

void Timer::Start() {
    active = true;

}

void Timer::Stop() {
    active = false;
}

void Timer::Update() {
    if(!active){
        return;
    }
    elapsed_time += GetFrameTime();
    if(elapsed_time >= wait_time) {
        EmitSignal(TIMER_TIMEOUT);
        active = false;
        finished = true;
    }
}

bool Timer::IsDone()
{
    return finished;
}

double Timer::TimeRemaining()
{
    return wait_time - elapsed_time;
}

double Timer::TimeElapsed() {
    return elapsed_time;
}

double Timer::GetWaitTime() {
    return wait_time;;
}

void SignalObserver::OnSignal(SIGNAL signal) {

}


void SignalEmiter::ConnectSignalTo(SignalObserver *_observer)
{
    observers.push_back(_observer);
}

void SignalEmiter::EmitSignal(SIGNAL signal) {
    for(int i = 0; i < observers.size(); i++) {
        observers[i]->OnSignal(signal);
    }
}


