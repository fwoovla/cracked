#pragma once

#include "global_def.h"

 
#include "bacescene.h"


class SceneManager{
    public:
    SceneManager();
    ~SceneManager();
    void UpdateScene();
    void DrawScene();
    void ChangeSceneTo(SCENE_ID new_scene);
    
    BaseScene *current_scene;

    private:
};

