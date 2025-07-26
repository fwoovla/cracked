#pragma once
#include <raylib.h>
#include "../globals.h"
#include "button.h"
#include "../utils/utils.h"

class BaseUILayer : public SignalEmiter {
    public:
    virtual ~BaseUILayer(){};
    virtual void Update() = 0;
    virtual void Draw() = 0;


    //std::vector<SignalObserver *> observers;

};