#pragma once
#include <raylib.h>
#include <string>

//#define LEVEL_SIZE 64
//#define TILE_SIZE 32
//#define INV_TILE_SIZE 1.0f/TILE_SIZE

struct  gameSettings {
    Vector2 window_size;
    Vector2 resolution;
    float game_scale;
    bool show_debug;
    int control_type;
    int level_num;
    Vector2 starting_position;
};

enum SCENE_ID {
    NO_SCENE,
    SPLASH_SCENE,
    TITLE_SCENE,
    STAGING_SCENE,
    GAME_SCENE,
};

/* enum COLLISION_LAYERS {
    COL_PLAYER_LAYER,
    COL_ENEMY_LAYER,
    COL_ALL_LAYER,

}; */
