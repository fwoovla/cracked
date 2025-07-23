#pragma once

#include "entity.h"
#include "sprite.h"

class Player : public DrawableEntity {
    public:
    Player();
    void Update() override;
    void Draw() override;

    Sprite sprite;

};