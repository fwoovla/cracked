#pragma once

//#include "global_def.h"

/* 
#include "button.h"
#include <raylib.h>
#include "../globals.h"
*/
#include "../utils/utils.h"

class BaseUILayer : public SignalEmiter {
    public:
    virtual ~BaseUILayer(){};
    virtual void Update() = 0;
    virtual void Draw() = 0;


    //std::vector<SignalObserver *> observers;

};