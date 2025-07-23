#pragma once
#include "../globals.h"
#include "../utils/utils.h"
#include "scenemanager.h"

class Game{
    public:
    Game();
    ~Game();
    void StartGame();
  
    private:
    bool running;
    SceneManager *scene_manager;
    
    //gameSettings &game_settings;

};