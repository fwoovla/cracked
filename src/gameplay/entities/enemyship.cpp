#include "../../core/global_def.h"
#include<cmath>
#include <raymath.h>


#define MIN_THRUST_TIME 50
#define MAX_THRUST_TIME 150
#define MIN_THRUST_WAIT 20
#define MAX_THRUST_WAIT 100


#define MIN_BURST_TIME 3
#define MAX_BURST_TIME 10

#define MIN_BURST_WAIT 50
#define MAX_BURST_WAIT 80

#define ENEMY_GUN_DELAY 0.1f

#define MAX_HEALTH 5

#define DETECT_RANGE 4

const float ROTATION_SPEED = PI * 0.4f; //<-do this more


EnemyShip::EnemyShip(Vector2 _position) : SpriteEntity() {

    position = _position;
    velocity = {0};
    rotation = 0.0f;
    id = GetRandomValue(0, 10000);
    LoadSpriteCentered(sprite, LoadTexture("assets/player.png"), {32*TILE_SIZE, 32*TILE_SIZE});
    
    centered_offset = {PLAYER_SIZE/2, PLAYER_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, PLAYER_SIZE, PLAYER_SIZE };
        
    sprite.dest.x = position.x;
    sprite.dest.y = position.y;
    
    should_delete = false;

    gun_timer = new Timer(GUN_DELAY, true, false);
    gun_timer->timout.Connect( [&](){this->OnGunTimerTimeout();} );
    gun_can_shoot = false;
    gun_power = GUN_MAX_POWER;
    shots = 0;
    target = nullptr;

    thrust_timer = new Timer(0.0f, false, false);
    thrust_timer->timout.Connect( [&](){this->OnThrustTimerTimeout();} );
    thrusting = false;

    thrust_wait_timer = new Timer(2.0f, false, false);
    thrust_wait_timer->timout.Connect( [&](){this->OnThrustWaitTimerTimeout();} );
    thrust_wait_timer->Start();
    can_thrust = false;

    health = MAX_HEALTH;

    burst_timer = new Timer(1.0f, false, false);
    bursting = false;
    burst_timer->timout.Connect( [&](){OnBurstTimerTimeout();} );

    burst_wait_timer = new Timer(GetRandomValue(0, 100) * 0.1f, false, false);
    can_burst = false;
    burst_wait_timer->timout.Connect( [&](){OnBurstWaitTimerTimeout();} );
    burst_wait_timer->Start();

    gun_sound = LoadSound("assets/laser2.wav");
    SetSoundVolume(gun_sound, 0.5f);

    hit_sound = LoadSound("assets/laserhit1.wav");

    detect_ray = {
        .position = {position.x, position.y},
        .direction = {100.0f, 0.0f},
    };

    ray_colliding = false;

    avoid_timer = new Timer(2.0f, false, false);
    avoid_timer->timout.Connect( [&](){OnAvoidTimerTimeout();} );
}


void EnemyShip::Update() {
    if(should_delete) {
        return;
    }

    float dt = GetFrameTime();

    gun_power += GetFrameTime() * GUN_REGEN;
    if (  gun_power > GUN_MAX_POWER) {
        gun_power = GUN_MAX_POWER;
    }
    DoMovement(dt);

    DoWeapons();
    gun_timer->Update();
    burst_timer->Update();
    burst_wait_timer->Update();
    thrust_timer->Update();
    thrust_wait_timer->Update();


    collisionResult result = {0};
    if(CheckCollisionWithBullets(this, result)) {
        Bullet *bullet = dynamic_cast<Bullet *>(result.collider);
        //TraceLog(LOG_INFO, "collided %i", bullet->shooter_id);
        if(bullet->shooter_id != id) {
            bullet->should_delete = true;
            health -=1;
            PlaySound(hit_sound);
            if(health <= 0) {
                should_delete = true;
                if(bullet->shooter_id == 1) {
                    player_killed_enemy.EmitSignal();
                }
            }
        }
    }
}

void EnemyShip::Draw() {

    DrawSprite(sprite);
    //DrawSprite(turret);

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

        if(collided) {
        //DrawCircleV(position, PLAYER_SIZE * 0.5, RED);
        DrawRectangleRec(collision_rect, RED);
        }
        else {
        //DrawCircleV(position, PLAYER_SIZE * 0.5, GREEN);
        DrawRectangleRec(collision_rect, GREEN);
        }
    }

    Vector2 a = {detect_ray.position.x, detect_ray.position.y};
    Vector2 b = {detect_ray.position.x + detect_ray.direction.x, detect_ray.position.y + detect_ray.direction.y};

    if(ray_colliding) {
        DrawLineV(a, b, RED);
    }
    else{
        DrawLineV(a, b, WHITE);
    }
}


void EnemyShip::DoMovement(float dt) {


    if(target) {

        detect_ray.position = {position.x, position.y};
        detect_ray.direction.x = Vector2Rotate({100,0}, DEG2RAD * rotation).x;
        detect_ray.direction.y = Vector2Rotate({100,0}, DEG2RAD * rotation).y;

        ray_colliding = false;
        collisionResult ray_result;
        if(GetRayCollisionWithLevel(detect_ray, ray_result, 0)) {
            ray_colliding = true;
        }

        Vector2 p1 = position;
        Vector2 p2 = {0};

        if(ray_colliding) {
            //p2 =  Vector2Add(position, detect_ray.direction) * -1.0f;
            avoid_timer->Start();
            avoiding = true;
        }
        if(avoiding) {
            avoid_timer->Update();
            rotation += 0.5f;
        }
        else {
            Vector2 p1 = position;
            Vector2 p2 = target->position;
            
            //        Vector2Rotate()
            float target_rotation = GetAngleFromTo(p1, p2);
            rotation = rotateTowardsRad(rotation * DEG2RAD, target_rotation, ROTATION_SPEED, dt) * RAD2DEG;
        }
    }


    //return;
    
    Vector2 previous_collision_position = {collision_rect.x, collision_rect.y};
    
    float thrust = SHIP_THRUST * 0.4f;
    float max_speed = PLAYER_SPEED * 0.4f;
    if(can_thrust) {
        if(GetRandomValue(0, 100) > 70) {
            //TraceLog(LOG_INFO, "THRUSTING");
            thrusting = true;
            can_thrust = false;
        }
    }
    if(thrusting) {
        thrust  = SHIP_THRUST * 0.7f;
        max_speed = PLAYER_SPEED * 0.7f;
        thrust_timer->wait_time = GetRandomValue(MIN_THRUST_TIME, MAX_THRUST_TIME) * 0.1;
        thrust_timer->Start();
    }

    float rad = rotation * DEG2RAD;
    velocity.x += cosf(rad) * thrust;
    velocity.y += sinf(rad) * thrust;

    velocity.x *= AIR_FRICTION;
    velocity.y *= AIR_FRICTION;

    vClamp(velocity, 1.0);

    velocity = Vector2ClampValue(velocity, -max_speed, max_speed);

    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
   
    collided = false;
    collisionResult collision_data = {0};
    if(CheckCollisionWithLevel(this, collision_data, DETECT_RANGE)) {
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
    sprite.roataion = rotation;
}


void EnemyShip::DoWeapons() {
    if(can_burst) {
        if(GetRandomValue(0, 100) > 70) {
            //TraceLog(LOG_INFO, "BURSTING");
            burst_timer->wait_time = GetRandomValue(MIN_BURST_TIME, MAX_BURST_TIME) * 0.1;
            bursting = true;
            can_burst = false;
            burst_timer->Start();
        }
    }
    if(bursting and gun_can_shoot) {
        gun_can_shoot = false;
        AddToDrawList(bullet_list, new Bullet(position, rotation, id));
        PlaySound(gun_sound);
    }
}


void EnemyShip::OnGunTimerTimeout() {
    //TraceLog(LOG_INFO, "SIGNAL RECIEVED");
    gun_can_shoot = true;
}

void EnemyShip::OnThrustTimerTimeout() {
    thrusting = false;
    //TraceLog(LOG_INFO, "END THRUSTING");
    thrust_wait_timer->wait_time = GetRandomValue(MIN_THRUST_WAIT, MAX_THRUST_WAIT) * 0.1f;
    thrust_wait_timer->Start();
}

void EnemyShip::OnThrustWaitTimerTimeout() {
    //TraceLog(LOG_INFO, "CAN THRUST");
    can_thrust = true;
}


void EnemyShip::OnBurstTimerTimeout() {
    bursting = false;
    //TraceLog(LOG_INFO, "END BURSTING");
    burst_wait_timer->wait_time = GetRandomValue(MIN_BURST_WAIT, MAX_BURST_WAIT) * 0.1f;
    burst_wait_timer->Start();
}

void EnemyShip::OnBurstWaitTimerTimeout() {
    //TraceLog(LOG_INFO, "CAN BURST");
    can_burst = true;
}

void EnemyShip::OnAvoidTimerTimeout() {
    //TraceLog(LOG_INFO, "CAN BURST");
    avoiding = false;
}

EnemyShip::~EnemyShip()
{
    AddToDrawList(effects_list, new ExplosionEffect(position));
    dead.EmitSignal();
    delete gun_timer;
    delete thrust_timer;
    delete thrust_wait_timer;
    delete avoid_timer;
    UnloadSound(gun_sound);
    UnloadSound(hit_sound);
    UnloadTexture(sprite.texture);
}
