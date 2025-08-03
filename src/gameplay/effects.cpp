#include "../core/global_def.h"
#include <raymath.h>

#define SIZE 16
#define LIFETIME 0.5f


BulletHit::BulletHit(Vector2 _position) {
    id = GetRandomValue(0, 10000);

    should_delete = false;
    //lifetime = new Timer(LIFETIME, true, true);
    //lifetime->timout.Connect([&](){this->OnLifetimeTimeout();});

    position = _position;
    
    LoadSpriteCentered(sprite, LoadTexture("assets/hit1.png"), position );
    sprite.roataion = rotation;

    centered_offset = {SIZE * 0.5, SIZE * 0.5};
  
}

BulletHit::~BulletHit() {
    UnloadTexture(sprite.texture);
    //delete lifetime;
}


void BulletHit::Update() {
    if(should_delete) {
        return;
    }

    float dt = GetFrameTime();

    sprite.modulate.a -= 10;
    //Lerp(sprite.modulate.a, 0, 0.01);
    if(sprite.modulate.a <= 50) {
        should_delete = true;
        TraceLog(LOG_INFO, "BULLET should delete %i", id);
    }

    //lifetime->Update();
}

void BulletHit::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
    }
}

/* 
void BulletHit::OnLifetimeTimeout() {
    //TraceLog(LOG_INFO, "BULLET should delete %i", id);
    should_delete =true;
} */