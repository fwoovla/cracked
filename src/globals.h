#pragma once
#include <raylib.h>
//#include "core/scenemanager.h"


#define MAX_SIGNAL_CONNECTIONS 256

enum SIGNAL {
    END_GAME,
    TIMER_TIMEOUT,
    PLAY_PRESSED,
};

enum SCENE_ID {
    NO_SCENE,
    TITLE_SCENE,
    GAME_SCENE,
};

struct  gameSettings {
    Vector2 window_size;
    bool show_debug;
};




//inline SceneManager *scenemanager;