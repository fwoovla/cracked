#include "../../core/global_def.h"
#include <raymath.h>



#define PICKUP_SIZE 32
//#define PICKUP_LIFETIME 1.0f

Pickup::Pickup(Vector2 _position) {
    id = GetRandomValue(0, 10000);
    collided = false;
    should_delete = false;

    position = _position;
    LoadSpriteCentered(sprite, LoadTexture("assets/pickup1.png"), position );

    centered_offset = {PICKUP_SIZE/2, PICKUP_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, PICKUP_SIZE, PICKUP_SIZE };
}


Pickup::~Pickup() {
    UnloadTexture(sprite.texture);
}


void Pickup::Update() {

    if(should_delete) {
        return;
    }

    float scalar = sin(GetTime());
    //TraceLog(LOG_INFO, "scalar %f, ", scalar);
    ScaleSprite(sprite, {scalar, scalar});

    collided = false;

    collisionResult result = {{0}, };
    collided = CheckCollisionWithEntities(this, result);
    if(collided) {
        if(result.collider->id == 1) {
            PlayerShip *playership = dynamic_cast<PlayerShip *>(result.collider);
            if(playership) {
                playership->OnPickup();
                should_delete = true;
            }
        }
    }

    collided = CheckCollisionWithBullets(this, result);
    if(collided) {
        result.collider->should_delete = true;
    } 
}

void Pickup::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug){
        if(collided) {
            DrawRectangleRec(collision_rect, RED);
        }
        else {
            DrawRectangleRec(collision_rect, GREEN);
        }
    }
}