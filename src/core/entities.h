#pragma once
#include "baseentity.h"
//#include "global_def.h"
#include "../utils/utils.h"



class Bullet :public DrawableEntity{
    public:
    Bullet(Vector2 _position, float _rotation);
    ~Bullet() override;
    void Update() override;
    void Draw() override;
    void OnLifetimeTimeout();

    Vector2 centered_offset;
    Vector2 velocity;
    Timer *lifetime;
};


class Pickup :public DrawableEntity{
    public:
    Pickup(Vector2 _position);
    ~Pickup() override;
    void Update() override;
    void Draw() override;

    Vector2 centered_offset;
    Vector2 velocity;
};

class BulletHit :public DrawableEntity{
    public:
    BulletHit(Vector2 _position);
    ~BulletHit() override;
    void Update() override;
    void Draw() override;
    //void OnLifetimeTimeout();

    Vector2 centered_offset;
    //Timer *lifetime;
};