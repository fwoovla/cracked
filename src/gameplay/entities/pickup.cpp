#include "../../core/global_def.h"
#include <raymath.h>



#define PICKUP_LIFETIME 1.0f

Pickup::Pickup(Vector2 _position) {
    id = GetRandomValue(0, 10000);
    should_delete = false;
    lifetime = new Timer(PICKUP_LIFETIME, true, true);
    lifetime->timout.Connect([&](){this->OnLifetimeTimeout();});

    position = _position;
    
    LoadSpriteCentered(sprite, LoadTexture("assets/laser1.png"), position );

}


Pickup::~Pickup() {
    UnloadTexture(sprite.texture);
    delete lifetime;
}

void Pickup::Update(int *level_array) {
    if(should_delete) {
        return;
    }

}

void Pickup::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
    }
}

bool Pickup::CheckCollision(collisionResult &collision_data) {
    return false;
}

void Pickup::OnLifetimeTimeout() {
    //TraceLog(LOG_INFO, "Pickup should delete %i", id);
    should_delete =true;
}