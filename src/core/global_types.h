#pragma once
#include <raylib.h>
//#include <vector>

#define LEVEL_SIZE 64
#define TILE_SIZE 32

struct  gameSettings {
    Vector2 window_size;
    bool show_debug;
    int control_type;
};

enum SCENE_ID {
    NO_SCENE,
    SPLASH_SCENE,
    TITLE_SCENE,
    GAME_SCENE,
};


