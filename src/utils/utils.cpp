#include "utils.h"

Timer::Timer(double _wait_time, bool _autostart, bool _one_shot) {
    wait_time = _wait_time;
    active = false;
    finished = false;
    elapsed_time = 0.0;
    one_shot = _one_shot;
    autostart = _autostart;


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
    //TraceLog(LOG_INFO,"TIMER");
    elapsed_time += GetFrameTime();
    if(elapsed_time >= wait_time) {

        timout.EmitSignal();
        active = false;
        finished = true;
        if(!one_shot) {
            elapsed_time = 0.0;
            //active = true;
            finished = false;
            Start();
        }
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

/* void SignalObserver::OnSignal(SIGNAL signal) {

}
 */

void Signal::Connect(std::function<void()> const& callback) {
    callbacks.push_back(callback);
}

void Signal::EmitSignal() {
    for(int i = 0; i < callbacks.size(); i++) {
        callbacks[i]();
 
    }
}   



