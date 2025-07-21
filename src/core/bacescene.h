#pragma once
#include <raylib.h>
#include "../globals.h"

class BaseScene {
    public:

    virtual SCENE_ID TickScene() = 0;
    virtual void DrawScene() = 0;
    virtual void DestroyScene() = 0;

    SCENE_ID scene_id;
};