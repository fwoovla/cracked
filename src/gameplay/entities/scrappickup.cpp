#include "../../core/global_def.h"
#include <raymath.h>


float AIR_FRICTION = 0.98f;
float MAX_VELOCITY = 4.0f;
#define PICKUP_SIZE 16
//#define PICKUP_LIFETIME 1.0f

ScrapPickup::ScrapPickup(Vector2 _position) {
    id = GetRandomValue(0, 10000);
    position = _position;
    rotation = GetRandomValue(0, 360);
    collided = false;
    should_delete = false;
    detect_radius = 100;
    detected = false;

    target = nullptr;
    velocity = Vector2Rotate({20,0}, rotation * DEG2RAD);
    
    LoadSpriteCentered(sprite, LoadTexture("assets/scrap.png"), position );

    centered_offset = {PICKUP_SIZE/2, PICKUP_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, PICKUP_SIZE, PICKUP_SIZE };
}


ScrapPickup::~ScrapPickup() {
    AddToDrawList(effects_list, new PickupEffect(position));
    UnloadTexture(sprite.texture);
}


void ScrapPickup::Update() {

    if(should_delete) {
        return;
    }

    sprite.roataion += 1.0f;

    collided = false;

    if(!detected){
        for(int i = 0; i < DRAW_LIST_SIZE; i++) {
            if(entity_list[i] != nullptr){
                if(entity_list[i]->id == 1){
                    if(CheckCollisionPointCircle(entity_list[i]->position, position,detect_radius)) {
                        detected = true;
                        target = entity_list[i];
                        float target_rotation = GetAngleFromTo(position, target->position);
                        //rotation = RotateTowardsRad(rotation * DEG2RAD, target_rotation, PI * 20, GetFrameTime()) * RAD2DEG;
                        rotation = target_rotation * RAD2DEG;
                        velocity = Vector2Rotate({MAX_VELOCITY, 0}, rotation * DEG2RAD );
                    }
                }
            }
        }
    }

    CollisionResult result = {{0}, };
    collided = CheckCollisionWithEntities(this, result);
    if(collided) {
        if(result.collider->id == 1) {
            PlayerShip *playership = dynamic_cast<PlayerShip *>(result.collider);
            if(playership) {
                playership->OnScrapPickup();
                should_delete = true;
                pickedup.EmitSignal();
            }
        }
    }


    if(detected and target) {
        TraceLog(LOG_INFO, "TARGET POSITION = %f %f", target->position.x, target->position.y);
        TraceLog(LOG_INFO, "ROTATION = %f", rotation);

        float target_rotation = GetAngleFromTo(position, target->position);
        //rotation = RotateTowardsRad(rotation * DEG2RAD, target_rotation, PI * 20, GetFrameTime()) * RAD2DEG;
        rotation = target_rotation * RAD2DEG;

        //velocity = Vector2Rotate(velocity, rotation * DEG2RAD);
        float rad = rotation * DEG2RAD;
        velocity.x += cosf(rad) * 0.2;
        velocity.y += sinf(rad) * 0.2;

        vClamp(velocity, 1.0);

        velocity = Vector2ClampValue(velocity, -MAX_VELOCITY , MAX_VELOCITY);
    }
    else {
        velocity.x *= AIR_FRICTION;
        velocity.y *= AIR_FRICTION;

        vClamp(velocity, 1.0);

        velocity = Vector2ClampValue(velocity, -1 , 1);

    }

    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
    position = {collision_rect.x +centered_offset.x, collision_rect.y +centered_offset.y};
    sprite.dest.x = position.x;
    sprite.dest.y = position.y;
}

void ScrapPickup::Draw() {
    DrawSprite(sprite);


    if(settings.show_debug){
        if(collided) {
            DrawRectangleRec(collision_rect, RED);
        }
        else {
            DrawRectangleRec(collision_rect, GREEN);
        }
        if(!detected){
            DrawCircleLinesV(position, detect_radius, WHITE);
        }
        else {
            DrawCircleLinesV(position, detect_radius, RED);
        }
    }
}