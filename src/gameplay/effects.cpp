#include "../core/global_def.h"
#include <raymath.h>

#define BULLET__HIT_SIZE 16
#define PICKUP_EFFECT_SIZE 32
#define EXPLODE_EFFECT_SIZE 64




BulletHit::BulletHit(Vector2 _position) {
    id = GetRandomValue(0, 10000);
    should_delete = false;
    position = _position;
    
    LoadSpriteCentered(sprite, LoadTexture("assets/hit1.png"), position);
    sprite.roataion = rotation;
    sprite.modulate.b += GetRandomValue(0, 200);

    centered_offset = {BULLET__HIT_SIZE * 0.5, BULLET__HIT_SIZE * 0.5};
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

    sprite.modulate.a -= 15;
    //Lerp(sprite.modulate.a, 0, 0.01);
    if(sprite.modulate.a <= 20) {
        should_delete = true;
        //TraceLog(LOG_INFO, "Effect should delete %i", id);
    }
}

void BulletHit::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
    }
}






PickupEffect::PickupEffect(Vector2 _position) {
    id = GetRandomValue(0, 10000);
    should_delete = false;
    position = _position;
    
    LoadSpriteCentered(sprite, LoadTexture("assets/pickupeffect1.png"), position);
    sprite.roataion = rotation;
    sprite.scale = {0};
    centered_offset = {PICKUP_EFFECT_SIZE * 0.5, PICKUP_EFFECT_SIZE * 0.5};
}

PickupEffect::~PickupEffect() {
    UnloadTexture(sprite.texture);
    //delete lifetime;
}

void PickupEffect::Update() {
    if(should_delete) {
        return;
    }

    float dt = GetFrameTime();

    ScaleSprite(sprite, {sprite.scale.x + 3.0f * dt, sprite.scale.y + 3.0f * dt});

    sprite.modulate.a = 255 - (sprite.scale.x * sprite.scale.x) * 40;

    if(sprite.scale.x >= 2.5) {
        should_delete = true;
    }
}

void PickupEffect::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
    }
}



ExplosionEffect::ExplosionEffect(Vector2 _position) {
    id = GetRandomValue(0, 10000);
    should_delete = false;
    position = _position;
    
    LoadSpriteCentered(sprite, LoadTexture("assets/explosion.png"), position);
    sprite.roataion = GetRandomValue(0, 360);
    sprite.scale = {0};
    centered_offset = {EXPLODE_EFFECT_SIZE * 0.5, EXPLODE_EFFECT_SIZE * 0.5};
}

ExplosionEffect::~ExplosionEffect() {
    UnloadTexture(sprite.texture);
    //delete lifetime;
}

void ExplosionEffect::Update() {
    if(should_delete) {
        return;
    }

    float dt = GetFrameTime();

    ScaleSprite(sprite, {sprite.scale.x +6.0f * dt, sprite.scale.y + 6.0f * dt});

    sprite.modulate.a = 255 - (sprite.scale.x * sprite.scale.x) * 40;

    if(sprite.scale.x >= 2.5) {
        should_delete = true;
    }
}

void ExplosionEffect::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
    }
}