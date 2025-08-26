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

    Vector2 centered_offset;
    Vector2 velocity;
    //Timer *lifetime;

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
    //Timer *lifetime;

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


inline void InitPlayerShip(PlayerData &_player_data) {
    _player_data.id = 1;


    _player_data.SIZE = 30;

    _player_data.AIR_FRICTION = 0.99f;
    _player_data.SHIP_BOUNCE_SCALEAR = 0.6f;

    _player_data.MAX_HEALTH = 10;

    _player_data.health = _player_data.MAX_HEALTH;
    _player_data.shots = 0;
    _player_data.points = 0;
    _player_data.scrap_amount = 0;
    
    _player_data.main_gun_part.part_name = main_gun_data[0].part_name;
    _player_data.main_gun_part.weight = main_gun_data[0].weight;
    _player_data.main_gun_part.GUN_MAX_POWER = main_gun_data[0].GUN_MAX_POWER;
    _player_data.main_gun_part.GUN_POWER_USE = main_gun_data[0].GUN_POWER_USE;
    _player_data.main_gun_part.GUN_REGEN = main_gun_data[0].GUN_REGEN;
    _player_data.main_gun_part.GUN_DELAY = main_gun_data[0].GUN_DELAY;
    _player_data.main_gun_part.cost = main_gun_data[0].cost;
    _player_data.gun_power = _player_data.main_gun_part.GUN_MAX_POWER;
    

    _player_data.thrusters_part.part_name = thrusters_data[0].part_name;
    _player_data.thrusters_part.weight = thrusters_data[0].weight;
    _player_data.thrusters_part.THRUSTER_SPEED = thrusters_data[0].THRUSTER_SPEED;
    _player_data.thrusters_part.THRUSTER_SHIP_THRUST = thrusters_data[0].THRUSTER_SHIP_THRUST;
    _player_data.thrusters_part.THRUSTER_SHIP_ROT_SPEED = thrusters_data[0].THRUSTER_SHIP_ROT_SPEED;
    _player_data.thrusters_part.cost = thrusters_data[0].cost;

    _player_data.armor_part.part_name = armors_data[0].part_name;
    _player_data.armor_part.weight = armors_data[0].weight;
    _player_data.armor_part.ARMOR = armors_data[0].ARMOR;
    _player_data.armor_part.cost = armors_data[0].cost;

}


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