#pragma once
#include "../globals.h"
#include "../utils/utils.h"
#include "scenemanager.h"

class Game{
    public:
    Game(gameSettings &_game_settings);
    ~Game();
    void StartGame();
  
    private:
    gameSettings game_settings;
    bool running;

    SceneManager *scene_manager;

};