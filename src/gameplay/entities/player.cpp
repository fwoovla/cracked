#include "../../core/entities.h"

Player::Player() : DrawableEntity() {
    LoadSpriteCentered(sprite, LoadTexture("assets/logo_pic_large.png"), {32*TILE_SIZE, 32*TILE_SIZE});
}

void Player::Update() {
    TraceLog(LOG_INFO, "PLAYER UPDATE");
}

void Player::Draw() {
    //TraceLog(LOG_INFO, "PLAYER DRAW");
    DrawSprite(sprite);
}