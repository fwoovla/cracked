#include "../../core/global_def.h"
#include<cmath>
#include <raymath.h>
//#include "ships.h"

//#include "../../core/entities.h"

EnemyShip::EnemyShip(Vector2 _position) : BaseShip() {

    position = _position;
    velocity = {0};
    rotation = 0.0f;
    id = 1;
    LoadSpriteCentered(sprite, LoadTexture("assets/player.png"), {32*TILE_SIZE, 32*TILE_SIZE});
    
    centered_offset = {PLAYER_SIZE/2, PLAYER_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, PLAYER_SIZE, PLAYER_SIZE };
    
    LoadSpriteCentered(turret, LoadTexture("assets/turret.png"), position);
    
    should_delete = false;

    gun_timer = new Timer(GUN_DELAY, true, false);
    gun_timer->timout.Connect( [&](){this->OnGunTimerTimeout();} );
    can_fire = false;
    gun_power = GUN_MAX_POWER;
    shots = 0;
}

void EnemyShip::Update() {
    float dt = GetFrameTime();

    gun_power += GetFrameTime() * GUN_REGEN;
    if (  gun_power > GUN_MAX_POWER) {
        gun_power = GUN_MAX_POWER;

    }
    

    //TraceLog(LOG_INFO, "PLAYER GUN POWER %f  %i", gun_power, shots);
    
    
    DoMovement(dt);
    DoWeapons();
    gun_timer->Update();

    collisionResult result;
    //collided = CheckCollisionWithEntities(this, result);


}

void EnemyShip::Draw() {
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


void EnemyShip::DoMovement(float dt) {

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

    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
   
    collided = false;
    collisionResult collision_data = {0};
    if(CheckCollisionWithLevel(this, collision_data)) {
        collided = true;
        //TraceLog(LOG_INFO, "COLLIED");
    }

    if(collided) {
        collision_rect.x = previous_collision_position.x;
        collision_rect.y = previous_collision_position.y;
        velocity = {-velocity.x * SHIP_BOUNCE_SCALEAR, -velocity.y * SHIP_BOUNCE_SCALEAR};
    }
    else {
        position = {collision_rect.x +centered_offset.x, collision_rect.y +centered_offset.y};
    }

    sprite.dest.x = position.x;
    sprite.dest.y = position.y;
    
    //Vector2 mp = GetMousePosition();
    //Vector2 pp = GetWorldToScreen2D(position, *camera);

    //turret.roataion = GetAngleFromTo(pp, mp);
}


void EnemyShip::DoWeapons() {


}


void EnemyShip::OnGunTimerTimeout() {
    //TraceLog(LOG_INFO, "SIGNAL RECIEVED");
    
    can_fire = true;

}

EnemyShip::~EnemyShip()
{
    UnloadTexture(sprite.texture);
    UnloadTexture(turret.texture);
}
