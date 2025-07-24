#pragma once

#include "entity.h"
#include "sprite.h"

class Player : public DrawableEntity {
    public:
    Player();
    void Update(int *level_data) override;
    void Draw() override;
    bool CheckCollision(Vector4 &collision_data, int *level_array) override;

    Sprite sprite;
    Rectangle collision_rect;
    bool player_collided;

};