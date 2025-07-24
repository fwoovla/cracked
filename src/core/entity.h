#pragma once
#include <raylib.h>
#include "../globals.h"
#include "../utils/utils.h"
#include "drawable.h"

class Entity  {
    public:
    virtual void Update(int *level_data) = 0;    
};

class DrawableEntity{
    public:
    virtual void Update(int *level_data) = 0;
    virtual void Draw() = 0;
    virtual bool CheckCollision(Vector4 &collision_data, int *level_array) = 0;
};