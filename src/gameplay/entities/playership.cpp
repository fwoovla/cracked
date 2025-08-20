#include "../../core/global_def.h"
#include<cmath>
#include <raymath.h>
//#include "ships.h"

//#include "../../core/entities.h"

#define DETECT_RANGE 3

PlayerShip::PlayerShip(Vector2 _position): AnimatedSpriteEntity() {

    //data = _data;
    position = settings.starting_position;
    velocity = {0};
    rotation = 0.0f;
    id = 1;

    LoadSpriteCentered(sprite, LoadTexture("assets/player_ship_frames.png"), {32*TILE_SIZE, 32*TILE_SIZE}, 3, 32.0f, 0.2f);
    
    centered_offset = {player_data.SIZE/2, player_data.SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, player_data.SIZE, player_data.SIZE };
    
    LoadSpriteCentered(turret, LoadTexture("assets/turret.png"), position);
    
    should_delete = false;

    gun_timer = new Timer(player_data.GUN_DELAY, true, false);
    gun_timer->timout.Connect( [&](){OnGunTimerTimeout();} );
    gun_can_shoot = false;
    //player_data.gun_power = player_data.GUN_MAX_POWER;
    //player_data.shots = 0;

    //player_data.health = player_data.MAX_HEALTH;

    thrust_timer = new Timer(0.3f, false, true);
    thrust_timer->timout.Connect( [&](){OnThrustTimerTimeout();} );
    thrusting = false;
    speed_cap = player_data.SPEED;
    thrust_cap = player_data.SHIP_THRUST;

    gun_sound = LoadSound("assets/laser.wav");
    SetSoundVolume(gun_sound, 0.6f);

    hit_sound = LoadSound("assets/laserhit1.wav");
    engine_sound = LoadSound("assets/engine1.wav");
    SetSoundVolume(engine_sound, 0.6f);

    alert_sound = LoadSound("assets/alert.wav");
    Reset();
}

void PlayerShip::Update() {
    if(player_data.health <= 0) {
        return;
    }

    float dt = GetFrameTime();

    if(player_data.health <= player_data.MAX_HEALTH * 0.2f) {
        if(!IsSoundPlaying(alert_sound)) {
            PlaySound(alert_sound);
        }
    }
    else {
        StopSound(alert_sound);
    }

    AnimateSprite(sprite);

    player_data.gun_power += dt * player_data.GUN_REGEN;
    if (  player_data.gun_power > player_data.GUN_MAX_POWER) {
        player_data.gun_power = player_data.GUN_MAX_POWER;
    }
    
    CollisionResult result = {0};
    if(CheckCollisionWithBullets(this, result)) {
        Bullet *bullet = dynamic_cast<Bullet *>(result.collider);
        //TraceLog(LOG_INFO, "collided %i", bullet->shooter_id);
        if(bullet->shooter_id != id) {
            PlaySound(hit_sound);
            player_hit.EmitSignal();
            result.collider->should_delete = true;
            player_data.health -=1;
            if(player_data.health <= 0) {
                dead.EmitSignal();
            }
        }
    }
    
    DoMovement(dt);
    DoWeapons();
    gun_timer->Update();
}

void PlayerShip::Draw() {
    if(player_data.health <= 0) {
        return;
    }

    DrawSprite(sprite);
    DrawSprite(turret);

    if(settings.show_debug){

        for(int x = -1; x <  DETECT_RANGE; x++) {
            for(int y = -1; y < DETECT_RANGE; y++) {
                float fx = collision_rect.x + (TILE_SIZE + x);
                float fy = collision_rect.y + (TILE_SIZE + y);
                int ix = (collision_rect.x/TILE_SIZE) + x;
                int iy = (collision_rect.y/TILE_SIZE) + y;

                if(level_array_data[(iy) * LEVEL_SIZE + (ix)] == 0) {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, PINK);
                }
                else {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, BLUE);
                }
            }
        }


        if(collided and settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
        }
        else {
        DrawRectangleRec(collision_rect, GREEN);
        }
    }
}


void PlayerShip::DoMovement(float dt) {
    if(settings.control_type == 0) {
        if (IsKeyDown(KEY_A)) {rotation -= player_data.SHIP_ROT_SPEED * dt;}
        if (IsKeyDown(KEY_D)) {rotation += player_data.SHIP_ROT_SPEED * dt;}
    }
    else if(settings.control_type == 1) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {rotation -= player_data.SHIP_ROT_SPEED * dt;}
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {rotation += player_data.SHIP_ROT_SPEED * dt;}
    }

    sprite.roataion = rotation;

    Vector2 previous_collision_position = {collision_rect.x, collision_rect.y};
    
    if (IsKeyDown(KEY_W)) {
        float rad = rotation * DEG2RAD;
        if(!IsSoundPlaying(engine_sound)) {
            PlaySound(engine_sound);
        }
        velocity.x += cosf(rad) * thrust_cap;
        velocity.y += sinf(rad) * thrust_cap;
    }

    if (IsKeyDown(KEY_S)) {
        if(!IsSoundPlaying(engine_sound)) {
            PlaySound(engine_sound);
        }
        float rad = rotation * DEG2RAD;
        velocity.x -= cosf(rad) * thrust_cap * .2;
        velocity.y -= sinf(rad) * thrust_cap * .2;
    }
    //else {StopSound(engine_sound);}
    if(!IsKeyDown(KEY_W) and !IsKeyDown(KEY_S)) {
        StopSound(engine_sound);
    }

    if(IsKeyDown(KEY_SPACE) and !thrusting and player_data.gun_power > player_data.GUN_MAX_POWER * 0.3) {
        player_data.gun_power -= (player_data.GUN_MAX_POWER * 0.3);
        speed_cap = player_data.SPEED * 5.0;
        thrust_cap = player_data.SHIP_THRUST * 8.0f;
        thrusting = true;
        thrust_timer->Start();
    }
    
    if(thrusting) {
        thrust_timer->Update();
        //TraceLog(LOG_INFO, "THRUSTING");
    }

    velocity.x *= player_data.AIR_FRICTION;
    velocity.y *= player_data.AIR_FRICTION;

    vClamp(velocity, 1.0);

    velocity = Vector2ClampValue(velocity, -speed_cap, speed_cap);

    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
   
    collided = false;
    CollisionResult collision_data = {0};
    if(CheckCollisionWithLevel(this, collision_data, DETECT_RANGE)) {
        collided = true;
        //TraceLog(LOG_INFO, "COLLIED");
    }

    if(collided) {
        collision_rect.x = previous_collision_position.x;
        collision_rect.y = previous_collision_position.y;
        velocity = {-velocity.x * player_data.SHIP_BOUNCE_SCALEAR, -velocity.y * player_data.SHIP_BOUNCE_SCALEAR};
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

    turret.roataion = GetAngleFromTo(pp, mp) * RAD2DEG;
}


void PlayerShip::DoWeapons() {

    if(settings.control_type == 0) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(gun_can_shoot and player_data.gun_power > player_data.GUN_POWER_USE ) {
                gun_can_shoot = false;
                AddToDrawList(bullet_list, new Bullet(position, turret.roataion, id));
                player_data.gun_power -= player_data.GUN_POWER_USE;
                shoot.EmitSignal();
                player_data.shots++;
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
    gun_can_shoot = true;
}

void PlayerShip::OnThrustTimerTimeout() {
    thrusting = false;
    speed_cap = player_data.SPEED;
    thrust_cap = player_data.SHIP_THRUST;
}


void PlayerShip::OnHealthPickup() {
    player_data.health = player_data.MAX_HEALTH;
}

void PlayerShip::OnScrapPickup() {
    player_data.scrap_amount += 1;
    scrap_picked_up.EmitSignal();
}


PlayerShip::~PlayerShip()
{
    delete gun_timer;
    delete thrust_timer;
    UnloadSound(gun_sound);
    UnloadSound(hit_sound);
    UnloadSound(engine_sound);
    UnloadSound(alert_sound);
    UnloadTexture(sprite.texture);
    UnloadTexture(turret.texture);
}

void PlayerShip::Reset() {
    speed_cap = player_data.SPEED;
    thrust_cap = player_data.SHIP_THRUST;
    player_data.health = player_data.MAX_HEALTH;
    player_data.gun_power = player_data.GUN_MAX_POWER;
    player_data.points = 0;
    player_data.shots = 0;
    player_data.scrap_amount = 0;
    position = settings.starting_position;
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, player_data.SIZE, player_data.SIZE };
    velocity = {0,0};
    rotation = 0.0f;
}