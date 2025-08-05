#pragma once

#include <raylib.h>
#include <vector>


#define LEVEL_SIZE 64
#define TILE_SIZE 32
#define INV_TILE_SIZE 1.0f/TILE_SIZE



#include "../utils/utils.h"
#include "uilayers.h"
#include "entities.h"
#include "ships.h"
#include "scenes.h"
#include "scenemanager.h"
#include "game.h"


extern gameSettings settings;
extern int* level_array_data;
extern  std::vector<DrawableEntity*> *collision_data_array[LEVEL_SIZE * LEVEL_SIZE];
extern bool game_running;