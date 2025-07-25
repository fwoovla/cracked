#include "../../core/entities.h"

Player::Player() : DrawableEntity() {
    LoadSprite(sprite, LoadTexture("assets/player.png"), {32*TILE_SIZE, 32*TILE_SIZE});
    collision_rect = { 32*TILE_SIZE, 32*TILE_SIZE, PLAYER_SIZE, PLAYER_SIZE };
}

Player::~Player() {
    UnloadTexture(sprite.texture);
}

void Player::Update(int *level_array) {
    //TraceLog(LOG_INFO, "PLAYER UPDATE");

    float dt = GetFrameTime();
    Vector2 previous_position = {collision_rect.x, collision_rect.y};

    collided = false;

    if (IsKeyDown(KEY_D)) collision_rect.x += PLAYER_SPEED * dt;
    else if (IsKeyDown(KEY_A)) collision_rect.x -= PLAYER_SPEED * dt;
            
    if (IsKeyDown(KEY_W)) collision_rect.y -= PLAYER_SPEED * dt;
    else if (IsKeyDown(KEY_S)) collision_rect.y += PLAYER_SPEED * dt;
    
    Vector4 collision_data = {0};
    if(CheckCollision(collision_data)) {
        collided = true;
    }

    if(collided) {
        collision_rect.x = previous_position.x;
        collision_rect.y = previous_position.y;
    }

    sprite.dest.x = collision_rect.x;
    sprite.dest.y = collision_rect.y;
}

void Player::Draw() {
    //TraceLog(LOG_INFO, "PLAYER DRAW");
    DrawSprite(sprite);
    if(collided) {
        DrawRectangleRec(collision_rect, RED);
    }
    else {
        DrawRectangleRec(collision_rect, GREEN);
    }
    
}

bool Player::CheckCollision(Vector4 &collision_data) {
    for(int x = -1; x <  COLLISION_RANGE; x++) {
        for(int y = -1; y < COLLISION_RANGE; y++) {

            float fx = collision_rect.x + (TILE_SIZE + x);
            float fy = collision_rect.y + (TILE_SIZE + y);
            int ix = (collision_rect.x/TILE_SIZE) + x;
            int iy = (collision_rect.y/TILE_SIZE) + y;

            if(level_array_data[(iy * LEVEL_SIZE + ix)] == 0) {

/*              TraceLog(LOG_INFO, "checking %i ", level_array[(y + iy) * LEVEL_SIZE + (x + ix)]);
                TraceLog(LOG_INFO, "checking cell at FLOAT %f %f ", fx, fy);
                TraceLog(LOG_INFO, "checking cell at index%i %i ", ix, iy);
                TraceLog(LOG_INFO, "checking rect at FLOAT %f %f \n", (float)ix * TILE_SIZE, (float)iy * TILE_SIZE);  */

                if(CheckCollisionRecs( collision_rect, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {                        return true;
                    return true;
                }
            }

        }
    }
    return false;
}