#pragma once

//#include "global_def.h"

/* 
#include "button.h"
#include <raylib.h>
#include "../globals.h"
*/
#include "../utils/utils.h"
#include "button.h"
#include "label.h"
#include "panel.h"
#include "labellist.h"

class BaseUILayer{
    public:
    virtual ~BaseUILayer(){};
    virtual void Update() = 0;
    virtual void Draw() = 0;

    //std::vector<SignalObserver *> observers;
};