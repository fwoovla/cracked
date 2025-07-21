#pragma once
#include "../globals.h"
#include "../utils/utils.h"
#include "scenemanager.h"

class Game : public SignalObserver {
    public:
    Game(gameSettings &_game_settings);
    ~Game();
    void StartGame();

    void OnSignal(SIGNAL signal) override;
    
    private:
    gameSettings game_settings;
    bool running;

    SceneManager *scene_manager;

};