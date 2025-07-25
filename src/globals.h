#pragma once
#include <raylib.h>
#include <vector>

//#include "core/scenemanager.h"


#define MAX_SIGNAL_CONNECTIONS 256
#define LEVEL_SIZE 64
#define TILE_SIZE 32

#define PLAYER_SPEED 3.0f
#define PLAYER_SIZE 30
#define COLLISION_RANGE 3
#define SHIP_THRUST 0.05f
#define SHIP_ROT_SPEED 180.0f
#define AIR_FRICTION 0.999f

#define DRAW_LIST_SIZE 100

#define BULLET_SIZE 10
#define BULLET_SPEED 600

enum SIGNAL {
    END_GAME,
    TIMER_TIMEOUT,
    PLAY_PRESSED,
    SHOULD_DELETE,
    CAN_FIRE
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