#pragma once
#include "baseship.h"
#include "../utils/utils.h"
#include "global_types.h"


/* #define PLAYER_SPEED 3.0f
#define PLAYER_SIZE 30
#define SHIP_THRUST 0.1f
#define SHIP_ROT_SPEED 180.0f
#define AIR_FRICTION 0.99f

#define SHIP_BOUNCE_SCALEAR 0.6f

#define PLAYER_GUN_MAX_POWER 10.0f
#define PLAYER_GUN_POWER_USE 1.0f
#define PLAYER_GUN_REGEN 3.0f
#define PLAYER_GUN_DELAY 0.2f */



struct PlayerData {
    float SPEED = 3.0f;
    float SIZE = 30;
    float SHIP_THRUST = 0.1f;
    float SHIP_ROT_SPEED = 180.0f;
    float AIR_FRICTION = 0.99f;
    float SHIP_BOUNCE_SCALEAR = 0.6f;
    float GUN_MAX_POWER = 10.0f;
    float GUN_POWER_USE = 1.0f;
    float GUN_REGEN = 3.0f;
    float GUN_DELAY = 0.2f;
};


struct EnemyData {
    int TYPE;
    float SPEED = 3.0;
    float SIZE = 30;
    float SHIP_THRUST = 0.1f;
    float SHIP_ROT_SPEED = 180.0f;
    float AIR_FRICTION = 0.99f;
    float SHIP_BOUNCE_SCALEAR = 0.6f;
    float MIN_THRUST_TIME = 50.0f;
    float MAX_THRUST_TIME = 150.0f;
    float MIN_THRUST_WAIT = 20.0f;
    float MAX_THRUST_WAIT = 100.0f;
    float MIN_BURST_TIME = 3.0f;
    float MAX_BURST_TIME = 10.0f;
    float MIN_BURST_WAIT = 50.0f;
    float MAX_BURST_WAIT = 80.0f;
    float GUN_DELAY = 0.1f;
    int MAX_HEALTH = 5;
    int DETECT_RANGE = 4;
    float ROTATION_SPEED = PI * 0.4f;
    float SHOOT_RANGE = 150000.0f;
    Texture2D texture;
};

class PlayerShip : public AnimatedSpriteEntity {
    public:
    PlayerShip(Vector2 _position, PlayerData _data);
    ~PlayerShip() override;
    void Update() override;
    void Draw() override;
    void Reset();
    void DoMovement(float dt);
    void DoWeapons();

    void OnGunTimerTimeout();
    void OnPickup();
    void OnHitEffectTimeout();

    
    PlayerData data;
    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;

    Texture2D turret_texture;
    Sprite turret;

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
    int shots;

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
        new_data.MAX_HEALTH = 5;
        new_data.DETECT_RANGE = 4;
        new_data.ROTATION_SPEED = PI * 0.4f;
        new_data.SHOOT_RANGE = 150000.0f;
        new_data.texture = LoadTexture("assets/enemy_ship_frames_1.png");
    };
    return new_data;
}