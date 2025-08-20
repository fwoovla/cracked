#pragma once
#include "baseship.h"
#include "../utils/utils.h"
#include "global_types.h"



class PlayerShip : public AnimatedSpriteEntity {
    public:
    PlayerShip(Vector2 _position);
    ~PlayerShip() override;
    void Update() override;
    void Draw() override;
    void Reset();
    void DoMovement(float dt);
    void DoWeapons();

    void OnGunTimerTimeout();
    void OnThrustTimerTimeout();
    void OnHealthPickup();
    void OnScrapPickup();
    void OnHitEffectTimeout();

    
    //PlayerData *data;

    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;

    Texture2D turret_texture;
    Sprite turret;

    Camera2D *camera;

    Timer *gun_timer;
    bool gun_can_shoot;

    Timer *thrust_timer;
    bool thrusting;
    float speed_cap;
    float thrust_cap;
    
    Signal shoot;
    Signal dead;
    Signal player_hit;
    Signal scrap_picked_up;
    
    Sound gun_sound;
    Sound hit_sound;
    Sound engine_sound;
    Sound alert_sound;
    
/*     float gun_power;
    int shots;
    int health;
    int points; */

};

class EnemyShip : public AnimatedSpriteEntity {
    public:
    EnemyShip(Vector2 _position, EnemyData _data);
    ~EnemyShip() override;
    void Update() override;
    void Draw() override;
    void DoMovement(float dt);
    void DoWeapons();

    void OnGunTimerTimeout();
    void OnThrustTimerTimeout();
    void OnThrustWaitTimerTimeout();
    void OnBurstTimerTimeout();
    void OnBurstWaitTimerTimeout();
    void OnPickup();
    void OnAvoidTimerTimeout();

    
    EnemyData data;

    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;

    //Texture2D turret_texture;
    //Sprite turret;
    Camera2D *camera;

    Timer *gun_timer;
    bool gun_can_shoot;
    bool shooting;
    //float gun_power;
    
    Signal shoot;
    Signal dead;
    Signal player_killed_enemy;
    
    BaseEntity *target;
    Vector2 target_position;
    float target_dist_sq;
    
    Timer *thrust_timer;
    Timer *thrust_wait_timer;
    bool thrusting;
    bool can_thrust;
    
    
    Timer *burst_timer;
    Timer *burst_wait_timer;
    
    bool can_burst;
    bool bursting;
    
    Sound gun_sound;
    Sound hit_sound;
    
    
    RayCast detect_ray;
    bool ray_colliding;
    Timer *avoid_timer;
    bool avoiding;
    
};

inline EnemyData CreateEnemy(int type) {

    EnemyData new_data;

    if(type == 0) {
        new_data.TYPE = type;
        new_data.SIZE = 30;
        new_data.SHIP_THRUST = 0.1f;
        new_data.SHIP_ROT_SPEED = 180.0f;
        new_data.AIR_FRICTION = 0.99f;
        new_data.SHIP_BOUNCE_SCALEAR = 0.6f;
        new_data.MIN_THRUST_TIME = 50.0f;
        new_data.MAX_THRUST_TIME = 150.0f;
        new_data.MIN_THRUST_WAIT = 20.0f;
        new_data.MAX_THRUST_WAIT = 100.0f;
        new_data.MIN_BURST_TIME = 3.0f;
        new_data.MAX_BURST_TIME = 5.0f;
        new_data.MIN_BURST_WAIT = 50.0f;
        new_data.MAX_BURST_WAIT = 80.0f;
        new_data.GUN_DELAY = 0.2f;
        new_data.DETECT_RANGE = 4;
        new_data.ROTATION_SPEED = PI * 0.8f;
        new_data.SHOOT_RANGE = 150000.0f; //dist squared
        new_data.texture = LoadTexture("assets/enemy_ship_frames_1.png");
        new_data.MAX_HEALTH = 1;

        new_data.shots = 0;
        new_data.health = new_data.MAX_HEALTH;
    };
    return new_data;
}