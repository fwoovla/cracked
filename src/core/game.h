#pragma once

#include "global_def.h"

/* 
#include "../globals.h"
#include "../utils/utils.h"
#include "scenemanager.h"

 */

class Game{
    public:
    Game();
    ~Game();
    void StartGame();
  
    private:
    //bool running;
    SceneManager *scene_manager;
    RenderTexture2D render_texture;
    
    //gameSettings &game_settings;

};