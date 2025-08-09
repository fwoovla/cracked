#pragma once
#include "baseship.h"
#include "../utils/utils.h"
#include "global_types.h"


#define PLAYER_SPEED 3.0f
#define PLAYER_SIZE 30
#define SHIP_THRUST 0.1f
#define SHIP_ROT_SPEED 180.0f
#define AIR_FRICTION 0.99f

#define SHIP_BOUNCE_SCALEAR 0.6f

#define GUN_MAX_POWER 10.0f
#define GUN_POWER_USE 1.0f
#define GUN_REGEN 3.0f
#define GUN_DELAY 0.2f


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
    void OnPickup();
    void OnHitEffectTimeout();

    
    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;

    Texture2D turret_texture;
    Sprite turret;
    //AnimatedSprite flame;

    Camera2D *camera;

    Timer *gun_timer;
    bool gun_can_shoot;
    float gun_power;
    int shots;

    Signal shoot;

    int health;

    Signal dead;
    Signal player_hit;

    Sound gun_sound;
    Sound hit_sound;
    Sound engine_sound;
    Sound alert_sound;

    int points;

};

class EnemyShip : public SpriteEntity {
    public:
    EnemyShip(Vector2 _position);
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

    
    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;

    //Texture2D turret_texture;
    //Sprite turret;
    Camera2D *camera;

    Timer *gun_timer;
    bool gun_can_shoot;
    bool shooting;
    float gun_power;
    int shots;

    Signal shoot;
    Signal dead;
    Signal player_killed_enemy;

    BaseEntity *target;
    Vector2 target_position;
    
    Timer *thrust_timer;
    Timer *thrust_wait_timer;
    bool thrusting;
    bool can_thrust;

    int health;

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