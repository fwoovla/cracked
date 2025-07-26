#include "../../core/entities.h"
#include <raymath.h>

//extern DrawableEntity *bullet;
Bullet::Bullet(Vector2 _position, float _rotation) {
    id = GetRandomValue(0, 10000);
    should_delete = false;
    lifetime = new Timer(2.0, true, true);
    lifetime->ConnectSignalTo(this);

    position = _position;
    rotation = _rotation;
    
    LoadSpriteCentered(sprite, LoadTexture("assets/laser1.png"), position );
    sprite.roataion = rotation;

    velocity = {BULLET_SPEED, 0};
    velocity = Vector2Rotate(velocity, rotation * DEG2RAD);
    TraceLog(LOG_INFO, "BULLET velocity %i  %f  %f   %f", id, velocity.x, velocity.y, rotation);

    centered_offset = {BULLET_SIZE/2, BULLET_SIZE/2};
    collision_rect = { position.x - centered_offset.x , position.y - centered_offset.y, BULLET_SIZE, BULLET_SIZE };
}


Bullet::~Bullet() {
    TraceLog(LOG_INFO, "BULLET DELETED DESTRUCTOR");
    UnloadTexture(sprite.texture);
    delete lifetime;
}


void Bullet::Update(int *level_array) {
    if(should_delete) {
        return;
    }
    Vector2 previous_collision_position = {collision_rect.x, collision_rect.y};
    //TraceLog(LOG_INFO, "BULLET velocity %i  %f  %f   %f", id, velocity.x, velocity.y, rotation);
    float dt = GetFrameTime();

    collision_rect.x += velocity.x * dt;
    collision_rect.y += velocity.y * dt;

    //position.x += velocity.x * dt;
    //position.y += velocity.y * dt;

    collided = false;
    collisionResult collision_data;
    if(CheckCollision(collision_data)) {
        collided = true;
    }

    if(collided) {
        collision_rect.x = previous_collision_position.x;
        collision_rect.y = previous_collision_position.y;
        velocity = {0};
    }
    else {
        position = {collision_rect.x +centered_offset.x, collision_rect.y +centered_offset.y};
    }

    sprite.dest.x = position.x;
    sprite.dest.y = position.y;

    lifetime->Update();
    //TraceLog(LOG_INFO, "BULLET Update");    
}

void Bullet::Draw() {
    DrawSprite(sprite);
    if(settings.show_debug) {
        DrawRectangleRec(collision_rect, RED);
    }
    //TraceLog(LOG_INFO, "BULLET Draw %i", id);
}

bool Bullet::CheckCollision(collisionResult &collision_data) {
    return false;
}

void Bullet::OnSignal(SIGNAL signal) {
    if(signal == TIMER_TIMEOUT) {
        TraceLog(LOG_INFO, "BULLET should delete %i", id);
        should_delete = true;

    }
}