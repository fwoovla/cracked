#pragma once
#include <raylib.h>
#include "../globals.h"
#include "button.h"
#include "../utils/utils.h"

class BaseUILayer : public SignalEmiter {
    public:

    ~BaseUILayer() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Destroy() = 0;


    //std::vector<SignalObserver *> observers;

};