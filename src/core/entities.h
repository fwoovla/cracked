#pragma once
#include "baseentity.h"
//#include "global_def.h"
#include "../utils/utils.h"



class Bullet :public DrawableEntity{
    public:
    Bullet(Vector2 _position, float _rotation);
    ~Bullet() override;
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(collisionResult &collision_data) override;
    void OnLifetimeTimeout();

    Rectangle collision_rect;
    Vector2 centered_offset;
    bool collided;
    Vector2 velocity;
    Vector2 position;
    float rotation;
    int id;
    Timer *lifetime;
};


class Pickup :public DrawableEntity{
    public:
    Pickup(Vector2 _position);
    ~Pickup() override;
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(collisionResult &collision_data) override;
    void OnLifetimeTimeout();

    Rectangle collision_rect;
    Vector2 centered_offset;
    bool collided;
    Vector2 velocity;
    Vector2 position;
    float rotation;
    int id;
    Timer *lifetime;
};

