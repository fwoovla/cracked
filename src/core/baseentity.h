#pragma once



/* 
#include "../utils/utils.h"
*/
//#include "global_types.h"
#include "global_def.h"
#include <raylib.h>
#include "sprite.h"


#define DRAW_LIST_SIZE 100
#define COLLISION_RANGE 3





class BaseEntity  {
    public:
    virtual void Update() = 0;    
};

class DrawableEntity{
    public:
    Sprite sprite;

    Rectangle collision_rect;
    bool should_delete;
    bool collided;
    Vector2 position;
    float rotation;
    int id;
    
    virtual ~DrawableEntity() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    //virtual bool CheckCollision(collisionResult &collision_data) = 0;

};



struct  collisionResult {
    Vector2 collision_dir;
    DrawableEntity *collider;
    
};


extern DrawableEntity *bullet_list[DRAW_LIST_SIZE];
extern DrawableEntity *entity_list[DRAW_LIST_SIZE];
extern DrawableEntity *effects_list[DRAW_LIST_SIZE];
extern int* level_array_data;



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

inline void DrawListUpdate(DrawableEntity *_draw_list[DRAW_LIST_SIZE]) {
    for(int i = 0; i < 100; i++) {
        if(_draw_list[i] != nullptr){
            _draw_list[i]->Update();
            if(_draw_list[i]->should_delete) {
                TraceLog(LOG_INFO, "DELETING ENTITY");
                delete _draw_list[i];
                _draw_list[i] = nullptr;
            }
        }
    }
}

inline bool CheckCollisionWithEntities(DrawableEntity *checker, collisionResult &collision_result) {
    if(checker->should_delete) {
        return false;
    }

    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(entity_list[i] != nullptr) {
            if(entity_list[i]->id == checker->id) {continue;}
            if(entity_list[i]->should_delete) {continue;}
            //TraceLog(LOG_INFO, "checking entities at index %i", i); 

            if(CheckCollisionRecs( checker->collision_rect, entity_list[i]->collision_rect)) {   
                //TraceLog(LOG_INFO, "COLLIDED"); 
                collision_result.collider = entity_list[i];
                //TraceLog(LOG_INFO, "COLLIDED %i", i);
                return true;
            } 
        }
    }
    return false;
}


inline bool CheckCollisionWithBullets(DrawableEntity *checker, collisionResult &collision_result) {
    if(checker->should_delete or checker->should_delete) {
        return false;
    }
     for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(bullet_list[i] != nullptr) {
            if(bullet_list[i]->id == checker->id) {continue;}
            if(bullet_list[i]->should_delete) {continue;}
            //TraceLog(LOG_INFO, "checking bullets at index %i", i); 

            if(CheckCollisionRecs( checker->collision_rect, bullet_list[i]->collision_rect)) {    
                collision_result.collider = bullet_list[i];
                //TraceLog(LOG_INFO, "COLLIDED %i", collision_result.collider->id);
                return true; 
            } 
        }
    } 
    return false;
}

inline bool CheckCollisionWithLevel(DrawableEntity *checker, collisionResult &collision_result) {
    //================TILE COLLISION=========================
    for(int x = -1; x <  COLLISION_RANGE; x++) {
        for(int y = -1; y < COLLISION_RANGE; y++) {

            float fx = checker->collision_rect.x + (TILE_SIZE + x);
            float fy = checker->collision_rect.y + (TILE_SIZE + y);
            int ix = (checker->collision_rect.x * INV_TILE_SIZE) + x;
            int iy = (checker->collision_rect.y * INV_TILE_SIZE) + y;
            if(level_array_data[(iy * LEVEL_SIZE + ix)] == 0) {

/*              TraceLog(LOG_INFO, "checking %i ", level_array[(y + iy) * LEVEL_SIZE + (x + ix)]);
                TraceLog(LOG_INFO, "checking cell at FLOAT %f %f ", fx, fy);
                TraceLog(LOG_INFO, "checking cell at index%i %i ", ix, iy);
                TraceLog(LOG_INFO, "checking rect at FLOAT %f %f \n", (float)ix * TILE_SIZE, (float)iy * TILE_SIZE);
                 if(CheckCollisionCircleRec( position, PLAYER_SIZE * 0.5, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {
                    return true;
                } 
*/
                if(CheckCollisionRecs( checker->collision_rect, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {
                    return true;
                }
            }
        }
    }

    return false;
}

