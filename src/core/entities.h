#pragma once
#include "baseentity.h"
//#include "global_def.h"
#include "../utils/utils.h"



class Bullet :public SpriteEntity{
    public:
    Bullet(Vector2 _position, float _rotation, int _shooter_id);
    ~Bullet() override;
    void Update() override;
    void Draw() override;
    void OnLifetimeTimeout();

    Vector2 velocity;
    Timer *lifetime;

    int shooter_id;
};


class Pickup :public SpriteEntity{
    public:
    Pickup(Vector2 _position);
    ~Pickup() override;
    void Update() override;
    void Draw() override;

    Signal pickedup;
};

class BulletHit :public SpriteEntity{
    public:
    BulletHit(Vector2 _position);
    ~BulletHit() override;
    void Update() override;
    void Draw() override;
    //void OnLifetimeTimeout();

    //Timer *lifetime;
};

class PickupEffect :public SpriteEntity{
    public:
    PickupEffect(Vector2 _position);
    ~PickupEffect() override;
    void Update() override;
    void Draw() override;
    //void OnLifetimeTimeout();

    //Timer *lifetime;
};

class ExplosionEffect :public SpriteEntity{
    public:
    ExplosionEffect(Vector2 _position);
    ~ExplosionEffect() override;
    void Update() override;
    void Draw() override;
    //void OnLifetimeTimeout();

    //Timer *lifetime;
};