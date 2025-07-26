#pragma once
#include <raylib.h>
#include <vector>

//#include "core/scenemanager.h"


#define MAX_SIGNAL_CONNECTIONS 256
#define LEVEL_SIZE 64
#define TILE_SIZE 32

#define PLAYER_SPEED 1.5f
#define PLAYER_SIZE 30
#define COLLISION_RANGE 3
#define SHIP_THRUST 0.02f
#define SHIP_ROT_SPEED 90.0f
#define AIR_FRICTION 0.99f

#define DRAW_LIST_SIZE 100

#define BULLET_SIZE 10
#define BULLET_SPEED 500

enum SIGNAL {
    END_GAME,
    TIMER_TIMEOUT,
    PLAY_PRESSED,
    SHOULD_DELETE,
    CAN_FIRE,
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

struct  collisionResult {
    Vector2 collision_dir;
    
};



extern gameSettings settings;
extern int* level_array_data;

//inline SceneManager *scenemanager;