#pragma once
#include "baseentity.h"

class Player : public DrawableEntity {
    public:
    Player();
    ~Player() override;
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(collisionResult &collision_data) override;

    Rectangle collision_rect;
    bool collided;
};

class Bullet :public DrawableEntity, public SignalObserver {
    public:
    Bullet(Vector2 _position, float _rotation);
    ~Bullet() override;
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(collisionResult &collision_data) override;
    void OnSignal(SIGNAL signal) override;

    Rectangle collision_rect;
    Vector2 centered_offset;
    bool collided;
    Vector2 velocity;
    Vector2 position;
    float rotation;
    int id;
    Timer *lifetime;
};

