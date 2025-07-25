#pragma once
#include <raylib.h>
#include "../globals.h"
#include "uilayers.h"
#include "../utils/utils.h"
#include "baseentity.h"

class BaseScene  {
    public:
    virtual ~BaseScene(){};
    virtual SCENE_ID Update() = 0;
    virtual void Draw() = 0;
    //virtual void OnSignal() = 0;
    
    
    SCENE_ID scene_id;
    SCENE_ID return_scene;
    

    
};