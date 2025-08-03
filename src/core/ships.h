#pragma once
#include "baseship.h"
#include "../utils/utils.h"
#include "global_types.h"


#define PLAYER_SPEED 1.5f
#define PLAYER_SIZE 30
#define SHIP_THRUST 0.02f
#define SHIP_ROT_SPEED 90.0f
#define AIR_FRICTION 0.99f

#define SHIP_BOUNCE_SCALEAR 0.6f

#define GUN_MAX_POWER 10.0f
#define GUN_POWER_USE 1.0f
#define GUN_REGEN 1.5f
#define GUN_DELAY 0.2f


class PlayerShip : public BaseShip {
    public:
    PlayerShip(Vector2 _position);
    ~PlayerShip() override;
    void Update() override;
    void Draw() override;
    //bool CheckCollision(collisionResult &collision_data) override;
    void DoMovement(float dt);
    void DoWeapons();

    void OnGunTimerTimeout();
    void OnPickup();

    
    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;

    Texture2D turret_texture;
    Sprite turret;
    Camera2D *camera;

    Timer *gun_timer;
    bool can_fire;
    float gun_power;
    int shots;

    Signal shoot;


};

