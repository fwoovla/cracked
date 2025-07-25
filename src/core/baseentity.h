#pragma once
#include <raylib.h>
#include "../globals.h"
#include "../utils/utils.h"

class BaseEntity  {
    public:
    virtual void Update(int *level_data) = 0;    
};

class DrawableEntity{
    public:
    virtual void Update(int *level_data) = 0;
    virtual void Draw() = 0;
    virtual bool CheckCollision(Vector4 &collision_data, int *level_array) = 0;

    bool should_delete;
};

//extern std::vector<DrawableEntity *> draw_list;
extern DrawableEntity *draw_list[DRAW_LIST_SIZE];


inline void AddToDrawList(DrawableEntity *new_entity) {
    
    for(int i = 0; i < 100; i++) {
        if(draw_list[i] == nullptr){
            draw_list[i] = new_entity;
            TraceLog(LOG_INFO, "ADDING DRAWABLE AT INDEX %i", i);
            return;
        }
    }
}