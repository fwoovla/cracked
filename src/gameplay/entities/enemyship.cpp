#include "../../core/global_def.h"
#include<cmath>
#include <raymath.h>


EnemyShip::EnemyShip(Vector2 _position, EnemyData _data) : AnimatedSpriteEntity() {

    data = _data;
    position = _position;
    velocity = {0};
    rotation = 0.0f;
    id = GetRandomValue(0, 10000);


    LoadSpriteCentered(sprite, data.texture, {32*TILE_SIZE, 32*TILE_SIZE}, 3, 32.0f, 0.1f);
    //LoadSpriteCentered(sprite, data.texture, {32*TILE_SIZE, 32*TILE_SIZE});

    
    centered_offset = {data.SIZE/2, data.SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, data.SIZE, data.SIZE };
        
    sprite.dest.x = position.x;
    sprite.dest.y = position.y;
    
    should_delete = false;

    gun_timer = new Timer(data.GUN_DELAY, true, false);
    gun_timer->timout.Connect( [&](){this->OnGunTimerTimeout();} );
    gun_can_shoot = false;
    //gun_power = data.GUN_MAX_POWER;
    data.shots = 0;
    target = nullptr;
    target_dist_sq = 0.0f;

    thrust_timer = new Timer(0.0f, false, false);
    thrust_timer->timout.Connect( [&](){this->OnThrustTimerTimeout();} );
    thrusting = false;

    thrust_wait_timer = new Timer(2.0f, false, false);
    thrust_wait_timer->timout.Connect( [&](){this->OnThrustWaitTimerTimeout();} );
    thrust_wait_timer->Start();
    can_thrust = false;

    data.health = data.MAX_HEALTH;

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

    AnimateSprite(sprite);

/*     gun_power += GetFrameTime() * GUN_REGEN;
    if (  gun_power > GUN_MAX_POWER) {
        gun_power = GUN_MAX_POWER;
    } */

    DoMovement(dt);

    DoWeapons();
    gun_timer->Update();
    burst_timer->Update();
    burst_wait_timer->Update();
    thrust_timer->Update();
    thrust_wait_timer->Update();


    CollisionResult result = {0};
    if(CheckCollisionWithBullets(this, result)) {
        Bullet *bullet = dynamic_cast<Bullet *>(result.collider);
        //TraceLog(LOG_INFO, "collided %i", bullet->shooter_id);
        if(bullet->shooter_id != id) {
            bullet->should_delete = true;
            data.health -=1;
            PlaySound(hit_sound);
            if(data.health <= 0) {
                should_delete = true;
                if(bullet->shooter_id == 1) {
                    player_killed_enemy.EmitSignal();
                    if(GetRandomValue(0, 100) > 50 ) {
                        AddToDrawList(entity_list, new ScrapPickup(position));
                    }
                }
            }
        }
    }
}

void EnemyShip::Draw() {

    DrawSprite(sprite);
    //DrawSprite(turret);

    if(settings.show_debug){
        for(int x = -1; x <  data.DETECT_RANGE; x++) {
            for(int y = -1; y < data.DETECT_RANGE; y++) {
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

        Vector2 a = {detect_ray.position.x, detect_ray.position.y};
        Vector2 b = {detect_ray.position.x + detect_ray.direction.x, detect_ray.position.y + detect_ray.direction.y};

        if(ray_colliding) {
            DrawLineV(a, b, RED);
        }
        else{
            DrawLineV(a, b, WHITE);
        }

        if(target_dist_sq > 150000.0f) {
           DrawCircle(position.x, position.y, 10, RED);
        }
        else {
            DrawCircle(position.x, position.y, 10, DARKGREEN);
        }
    }
}


void EnemyShip::DoMovement(float dt) {

    if(target) {

        detect_ray.position = {position.x, position.y};
        detect_ray.direction.x = Vector2Rotate({100,0}, DEG2RAD * rotation).x;
        detect_ray.direction.y = Vector2Rotate({100,0}, DEG2RAD * rotation).y;

        ray_colliding = false;
        CollisionResult ray_result;
        if(GetRayCollisionWithLevel(detect_ray, ray_result, 0)) {
            ray_colliding = true;
        }

        Vector2 p1 = position;
        Vector2 p2 = {0};

        if(ray_colliding) {
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
            rotation = RotateTowardsRad(rotation * DEG2RAD, target_rotation, data.ROTATION_SPEED, dt) * RAD2DEG;
        }
    }
    Vector2 end = Vector2Subtract(position, target->position);
    float x_sq = abs(end.x * end.x);
    float y_sq = abs(end.y * end.y);
    target_dist_sq = x_sq + y_sq;
    //TraceLog(LOG_INFO, "DISTANCE TO PLAYER %f", target_dist_sq);

    //return;
    
    Vector2 previous_collision_position = {collision_rect.x, collision_rect.y};
    
    float thrust = data.SHIP_THRUST * 0.4f;
    float max_speed = data.SPEED * 0.4f;
    if(can_thrust) {
        if(GetRandomValue(0, 100) > 70) {
            //TraceLog(LOG_INFO, "THRUSTING");
            thrusting = true;
            can_thrust = false;
        }
    }
    if(thrusting) {
        thrust  = data.SHIP_THRUST * 0.7f;
        max_speed = data.SPEED * 0.7f;
        thrust_timer->wait_time = GetRandomValue(data.MIN_THRUST_TIME, data.MAX_THRUST_TIME) * 0.1;
        thrust_timer->Start();
    }

    float rad = rotation * DEG2RAD;
    velocity.x += cosf(rad) * thrust;
    velocity.y += sinf(rad) * thrust;

    velocity.x *= data.AIR_FRICTION;
    velocity.y *= data.AIR_FRICTION;

    vClamp(velocity, 1.0);

    velocity = Vector2ClampValue(velocity, -max_speed, max_speed);

    collision_rect.x += velocity.x;
    collision_rect.y += velocity.y;
   
    collided = false;
    CollisionResult collision_data = {0};
    if(CheckCollisionWithLevel(this, collision_data, data.DETECT_RANGE)) {
        collided = true;
        //TraceLog(LOG_INFO, "COLLIED");
    }

    if(collided) {
        collision_rect.x = previous_collision_position.x;
        collision_rect.y = previous_collision_position.y;
        velocity = {-velocity.x * data.SHIP_BOUNCE_SCALEAR, -velocity.y * data.SHIP_BOUNCE_SCALEAR};
    }
    else {
        position = {collision_rect.x +centered_offset.x, collision_rect.y +centered_offset.y};
    }

    sprite.dest.x = position.x;
    sprite.dest.y = position.y;
    sprite.roataion = rotation;
}


void EnemyShip::DoWeapons() {
    if(target_dist_sq > 150000.0f) {
        return;
    }

    if(can_burst) {
        if(GetRandomValue(0, 100) > 70) {
            //TraceLog(LOG_INFO, "BURSTING");
            burst_timer->wait_time = GetRandomValue(data.MIN_BURST_TIME, data.MAX_BURST_TIME) * 0.1;
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
    thrust_wait_timer->wait_time = GetRandomValue(data.MIN_THRUST_WAIT, data.MAX_THRUST_WAIT) * 0.1f;
    thrust_wait_timer->Start();
}

void EnemyShip::OnThrustWaitTimerTimeout() {
    //TraceLog(LOG_INFO, "CAN THRUST");
    can_thrust = true;
}

void EnemyShip::OnBurstTimerTimeout() {
    bursting = false;
    //TraceLog(LOG_INFO, "END BURSTING");
    burst_wait_timer->wait_time = GetRandomValue(data.MIN_BURST_WAIT, data.MAX_BURST_WAIT) * 0.1f;
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
