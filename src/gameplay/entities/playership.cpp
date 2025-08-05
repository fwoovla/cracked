#include "../../core/global_def.h"
#include<cmath>
#include <raymath.h>
//#include "ships.h"

//#include "../../core/entities.h"
#define MAX_HEALTH 10

PlayerShip::PlayerShip(Vector2 _position) : BaseShip() {

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
    gun_can_shoot = false;
    gun_power = GUN_MAX_POWER;
    shots = 0;

    health = MAX_HEALTH;

    gun_sound = LoadSound("assets/laser.wav");
    SetSoundVolume(gun_sound, 0.6f);

    hit_sound = LoadSound("assets/laserhit1.wav");
    engine_sound = LoadSound("assets/engine1.wav");
    SetSoundVolume(engine_sound, 0.6f);

}

void PlayerShip::Update() {
    if(health <= 0) {
        return;
    }

    float dt = GetFrameTime();

    gun_power += GetFrameTime() * GUN_REGEN;
    if (  gun_power > GUN_MAX_POWER) {
        gun_power = GUN_MAX_POWER;

    }
    
    collisionResult result = {0};
    if(CheckCollisionWithBullets(this, result)) {
        Bullet *bullet = dynamic_cast<Bullet *>(result.collider);
        //TraceLog(LOG_INFO, "collided %i", bullet->shooter_id);
        if(bullet->shooter_id != id) {
            PlaySound(hit_sound);
            player_hit.EmitSignal();
            result.collider->should_delete = true;
            health -=1;
            if(health <= 0) {
                dead.EmitSignal();
            }
        }
    }
    
    DoMovement(dt);
    DoWeapons();
    gun_timer->Update();
}

void PlayerShip::Draw() {
    if(health <= 0) {
        return;
    }
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


void PlayerShip::DoMovement(float dt) {
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
        float rad = rotation * DEG2RAD;
        if(!IsSoundPlaying(engine_sound)) {
            PlaySound(engine_sound);
        }
        velocity.x += cosf(rad) * SHIP_THRUST;
        velocity.y += sinf(rad) * SHIP_THRUST;
    }
    //else {StopSound(engine_sound);}

    if (IsKeyDown(KEY_S)) {
        if(!IsSoundPlaying(engine_sound)) {
            PlaySound(engine_sound);
        }
        float rad = rotation * DEG2RAD;
        velocity.x -= cosf(rad) * SHIP_THRUST * .2;
        velocity.y -= sinf(rad) * SHIP_THRUST * .2;
    }
    //else {StopSound(engine_sound);}
    if(!IsKeyDown(KEY_W) and !IsKeyDown(KEY_S)) {
        StopSound(engine_sound);
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
    turret.dest.x = position.x;
    turret.dest.y = position.y;
    
    Vector2 mp = GetMousePosition();
    Vector2 pp = GetWorldToScreen2D(position, *camera);

    turret.roataion = GetAngleFromTo(pp, mp);
}


void PlayerShip::DoWeapons() {

    if(settings.control_type == 0) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(gun_can_shoot and gun_power > GUN_POWER_USE ) {
                gun_can_shoot = false;
                AddToDrawList(bullet_list, new Bullet(position, turret.roataion, id));
                gun_power -= GUN_POWER_USE;
                shoot.EmitSignal();
                shots++;
                PlaySound(gun_sound);
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


void PlayerShip::OnGunTimerTimeout() {
    //TraceLog(LOG_INFO, "SIGNAL RECIEVED");
    
    gun_can_shoot = true;

}

void PlayerShip::OnPickup() {
    //TraceLog(LOG_INFO, "PLAYER GOT A PICKUP!!");
    health = MAX_HEALTH;
}

PlayerShip::~PlayerShip()
{
    delete gun_timer;
    UnloadSound(gun_sound);
    UnloadSound(hit_sound);
    UnloadSound(engine_sound);
    UnloadTexture(sprite.texture);
    UnloadTexture(turret.texture);
}

void PlayerShip::Reset() {
    health = MAX_HEALTH;
    gun_power = GUN_MAX_POWER;
}