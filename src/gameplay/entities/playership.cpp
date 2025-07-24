#include "../../core/ships.h"
#include<cmath>
#include <raymath.h>

PlayerShip::PlayerShip(Vector2 _position) : BaseShip() {
    position = _position;
    velocity = {0};
    rotation = 0.0f;
    LoadSpriteCentered(sprite, LoadTexture("assets/player.png"), {32*TILE_SIZE, 32*TILE_SIZE});

    centered_offset = {PLAYER_SIZE/2, PLAYER_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, PLAYER_SIZE, PLAYER_SIZE };

    LoadSpriteCentered(turret, LoadTexture("assets/turret.png"), position);
    //LoadTexture("assets/turret.png");
}

PlayerShip::~PlayerShip() {
    UnloadTexture(sprite.texture);
    UnloadTexture(turret.texture);
}

void PlayerShip::Update(int *level_array) {
    float dt = GetFrameTime();
    DoMovement(dt, level_array);
}

void PlayerShip::Draw() {
    //TraceLog(LOG_INFO, "PLAYER DRAW");

    DrawSprite(sprite);
    DrawSprite(turret);

    if(settings.show_debug){
        if(player_collided and settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
        }
        else {
        DrawRectangleRec(collision_rect, GREEN);
        }
    }
}


void PlayerShip::DoMovement(float dt, int *level_array) {
    if(settings.control_type == 0) {
        if (IsKeyDown(KEY_A)) {rotation -= SHIP_ROT_SPEED * dt;}
        if (IsKeyDown(KEY_D)) {rotation += SHIP_ROT_SPEED * dt;}
    }
    else if(settings.control_type == 1) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {rotation -= SHIP_ROT_SPEED * dt;}
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {rotation += SHIP_ROT_SPEED * dt;}
    }

    sprite.roataion = rotation;

    Vector2 previous_collision_position = {collision_rect.x, collision_rect.y};
    
    if (IsKeyDown(KEY_W)) {
        // Convert angle to radians
        float rad = rotation * DEG2RAD;
        // Apply acceleration in facing direction
        velocity.x += cosf(rad) * SHIP_THRUST;
        velocity.y += sinf(rad) * SHIP_THRUST;
    }

    velocity.x *= AIR_FRICTION;
    velocity.y *= AIR_FRICTION;

    vClamp(velocity, 1.0);

    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
   
    player_collided = false;
    Vector4 collision_data = {0};
    if(CheckCollision(collision_data, level_array)) {
        player_collided = true;
    }

    if(player_collided) {
        collision_rect.x = previous_collision_position.x;
        collision_rect.y = previous_collision_position.y;
        velocity = {0};
    }
    else {
        position = {collision_rect.x +centered_offset.x, collision_rect.y +centered_offset.y};
    }

    sprite.dest.x = position.x;
    sprite.dest.y = position.y;
    turret.dest.x = position.x;
    turret.dest.y = position.y;
    
    Vector2 mp = GetMousePosition();
    Vector2 pp = GetWorldToScreen2D(position, *camera);

    turret.roataion = GetAngleFromTo(pp, mp);

}


bool PlayerShip::CheckCollision(Vector4 &collision_data, int *level_array) {
    for(int x = -1; x <  COLLISION_RANGE; x++) {
        for(int y = -1; y < COLLISION_RANGE; y++) {

            float fx = collision_rect.x + (TILE_SIZE + x);
            float fy = collision_rect.y + (TILE_SIZE + y);
            int ix = (collision_rect.x/TILE_SIZE) + x;
            int iy = (collision_rect.y/TILE_SIZE) + y;

            if(level_array[(iy * LEVEL_SIZE + ix)] == 0) {

/*              TraceLog(LOG_INFO, "checking %i ", level_array[(y + iy) * LEVEL_SIZE + (x + ix)]);
                TraceLog(LOG_INFO, "checking cell at FLOAT %f %f ", fx, fy);
                TraceLog(LOG_INFO, "checking cell at index%i %i ", ix, iy);
                TraceLog(LOG_INFO, "checking rect at FLOAT %f %f \n", (float)ix * TILE_SIZE, (float)iy * TILE_SIZE);  */

                if(CheckCollisionRecs( collision_rect, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {                        return true;
                    //player_collided = true;
                    //TraceLog(LOG_INFO, "COLLISION");
                    return true;
                }
            }
        }
    }
    return false;
}

