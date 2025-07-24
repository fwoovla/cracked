#pragma once
#include <raylib.h>
//#include "core/scenemanager.h"


#define MAX_SIGNAL_CONNECTIONS 256
#define LEVEL_SIZE 64
#define TILE_SIZE 32
#define PLAYER_SPEED 3
#define PLAYER_SIZE 30
#define COLLISION_RANGE 3
#define SHIP_THRUST 0.05f
#define SHIP_ROT_SPEED 180.0f
#define AIR_FRICTION 0.99f

enum SIGNAL {
    END_GAME,
    TIMER_TIMEOUT,
    PLAY_PRESSED,
};

enum SCENE_ID {
    NO_SCENE,
    SPLASH_SCENE,
    TITLE_SCENE,
    GAME_SCENE,
};

struct  gameSettings {
    Vector2 window_size;
    bool show_debug;
    int control_type;
};


extern gameSettings settings;

//inline SceneManager *scenemanager;