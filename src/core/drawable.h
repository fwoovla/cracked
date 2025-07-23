#pragma once
#include <raylib.h>
#include "../globals.h"
#include "uilayers.h"
#include "../utils/utils.h"

class Drawable  {
    public:
    virtual void Draw() = 0;
    
};