#pragma once
#include <raylib.h>
#include "../globals.h"
#include "../utils/utils.h"
#include "drawable.h"

class Entity  {
    public:
    virtual void Update() = 0;    
};

class DrawableEntity{
    public:
    virtual void Update() = 0;
    virtual void Draw() = 0;
};