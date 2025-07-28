#pragma once



/* 
#include "../globals.h"
#include "../utils/utils.h"
*/
#include <raylib.h>
#include "sprite.h"


#define DRAW_LIST_SIZE 100


struct  collisionResult {
    Vector2 collision_dir;
    
};


class BaseEntity  {
    public:
    virtual void Update(int *level_data) = 0;    
};

class DrawableEntity{
    public:
    Sprite sprite;

    virtual ~DrawableEntity() = default;
    virtual void Update(int *level_data) = 0;
    virtual void Draw() = 0;
    virtual bool CheckCollision(collisionResult &collision_data) = 0;

    bool should_delete;
};


extern DrawableEntity *bullet_list[DRAW_LIST_SIZE];
extern DrawableEntity *entity_list[DRAW_LIST_SIZE];




/* inline bool EntityCheckCollision(DrawableEntity *_entity, Vector4 &collision_data) {
    return false;
} */


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
        if(_draw_list[i] != nullptr){
            _draw_list[i]->Draw();
        }
    }
}

inline void DrawListUpdate(DrawableEntity *_draw_list[DRAW_LIST_SIZE], int *level_data) {
    for(int i = 0; i < 100; i++) {
        if(_draw_list[i] != nullptr){
            _draw_list[i]->Update(level_data);
            if(_draw_list[i]->should_delete) {
                TraceLog(LOG_INFO, "DELETING ENTITY");
                delete _draw_list[i];
                _draw_list[i] = nullptr;
            }
        }
    }
}


