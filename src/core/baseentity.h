#pragma once
#include <raylib.h>
#include "../globals.h"
#include "../utils/utils.h"
#include "sprite.h"


class BaseEntity  {
    public:
    virtual void Update(int *level_data) = 0;    
};

class DrawableEntity{
    public:
    Sprite sprite;

    virtual ~DrawableEntity(){};
    virtual void Update(int *level_data) = 0;
    virtual void Draw() = 0;
    virtual bool CheckCollision(Vector4 &collision_data) = 0;

    bool should_delete;
};


extern DrawableEntity *bullet_list[DRAW_LIST_SIZE];
extern DrawableEntity *entity_list[DRAW_LIST_SIZE];
//extern std::vector<DrawableEntity *> draw_list;


inline void AddToDrawList(DrawableEntity *_draw_list[DRAW_LIST_SIZE], DrawableEntity *new_entity) {
    
    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(_draw_list[i] == nullptr){
            _draw_list[i] = new_entity;
            TraceLog(LOG_INFO, "ADDING DRAWABLE AT INDEX %i", i);
            return;
        }
    }
}


inline void DrawListDraw(DrawableEntity *_draw_list[DRAW_LIST_SIZE]) {
    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(_draw_list[i] == nullptr){
            _draw_list[i]->Draw();
            return;
        }
    }
}

inline void DrawListUpdate(DrawableEntity *_draw_list[DRAW_LIST_SIZE]) {
    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(_draw_list[i] == nullptr){
            _draw_list[i]->Update(level_array_data);
            return;
        }
    }
}


