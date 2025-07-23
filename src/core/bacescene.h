#pragma once
#include <raylib.h>
#include "../globals.h"
#include "uilayers.h"
#include "../utils/utils.h"

class BaseScene  {
    public:
    //BaseScene();
    virtual SCENE_ID Update() = 0;
    virtual void Draw() = 0;
    virtual void Destroy() = 0;
    //virtual void OnSignal() = 0;
    
    
    SCENE_ID scene_id;
    SCENE_ID return_scene;

    
};