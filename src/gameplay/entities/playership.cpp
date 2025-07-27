#include "../../core/global_def.h"
#include<cmath>
#include <raymath.h>

//#include "../../core/entities.h"

PlayerShip::PlayerShip(Vector2 _position) : BaseShip() {

    position = _position;
    velocity = {0};
    rotation = 0.0f;
    LoadSpriteCentered(sprite, LoadTexture("assets/player.png"), {32*TILE_SIZE, 32*TILE_SIZE});

    centered_offset = {PLAYER_SIZE/2, PLAYER_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, PLAYER_SIZE, PLAYER_SIZE };

    LoadSpriteCentered(turret, LoadTexture("assets/turret.png"), position);

    should_delete = false;

    gun_timer = new Timer(1.0, true, false);
    gun_timer->ConnectSignalTo(this);
    can_fire = false;
    //LoadTexture("assets/turret.png");
}

void PlayerShip::Update(int *level_array) {
    float dt = GetFrameTime();
    DoMovement(dt, level_array);
    DoWeapons();
    gun_timer->Update();

}

void PlayerShip::Draw() {
    //TraceLog(LOG_INFO, "PLAYER DRAW");

    

    DrawSprite(sprite);
    DrawSprite(turret);

    if(settings.show_debug){
        if(collided and settings.show_debug) {
        //DrawCircleV(position, PLAYER_SIZE * 0.5, RED);
        DrawRectangleRec(collision_rect, RED);
        }
        else {
        //DrawCircleV(position, PLAYER_SIZE * 0.5, GREEN);
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
    if (IsKeyDown(KEY_S)) {
        // Convert angle to radians
        float rad = rotation * DEG2RAD;
        // Apply acceleration in facing direction
        velocity.x -= cosf(rad) * SHIP_THRUST * .2;
        velocity.y -= sinf(rad) * SHIP_THRUST * .2;
    }

    velocity.x *= AIR_FRICTION;
    velocity.y *= AIR_FRICTION;

    vClamp(velocity, 1.0);

    velocity = Vector2ClampValue(velocity, -PLAYER_SPEED, PLAYER_SPEED);
    //TraceLog(LOG_INFO, "VELOCITY: %f %f", velocity.x,velocity.y);


    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
   
    collided = false;
    collisionResult collision_data = {0};
    if(CheckCollision(collision_data)) {
        collided = true;
    }

    if(collided) {
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


bool PlayerShip::CheckCollision(collisionResult &collision_result) {
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
/*                 if(CheckCollisionCircleRec( position, PLAYER_SIZE * 0.5, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {
                    return true;
                } */
                if(CheckCollisionRecs( collision_rect, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {                        return true;
                    return true;
                }
            }
        }
    }
    return false;
}

void PlayerShip::DoWeapons() {

    if(settings.control_type == 0) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(can_fire) {
                can_fire = false;
                TraceLog(LOG_INFO, "FIRE 1");
                AddToDrawList(bullet_list, new Bullet(position, turret.roataion));
            }
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) ) {
            TraceLog(LOG_INFO, "FIRE 2");
        }
    }

    else if(settings.control_type == 1) {
        if(IsKeyDown(KEY_SPACE)) {
            TraceLog(LOG_INFO, "FIRE 1");
        }
        if(IsKeyDown(KEY_LEFT_SHIFT)) {
            TraceLog(LOG_INFO, "FIRE 2");
        }
    }
}


void PlayerShip::OnSignal(SIGNAL signal) {
    if(signal == TIMER_TIMEOUT){
        //TraceLog(LOG_INFO, "can shoot");
        can_fire = true;
    }
}

PlayerShip::~PlayerShip() {
    UnloadTexture(sprite.texture);
    UnloadTexture(turret.texture);
}

