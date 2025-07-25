#pragma once
#include <raylib.h>
#include "../globals.h"
#include "uilayers.h"
#include "../utils/utils.h"
#include "baseentity.h"
#include "sprite.h"

class BaseShip : public DrawableEntity {
    public:

    virtual void Update(int *level_data) = 0;
    virtual void Draw() = 0;
    virtual bool CheckCollision(Vector4 &collision_data) = 0;
    
    
};