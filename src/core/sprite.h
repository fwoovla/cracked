#pragma once
#include <raylib.h>
//#include "../globals.h"

struct Sprite {
    Texture2D texture;
    Vector2 position;
    Vector2 center;
    Vector2 size;
    Rectangle source;
    Rectangle dest;
    Vector2 scale;
    float roataion;
    Color modulate;
};



inline void LoadSpriteCentered(Sprite &_sprite, Texture2D _texture, Vector2 _position) {
    _sprite.texture = _texture;
    _sprite.size = {(float)_texture.width, (float)_texture.height};
    _sprite.position = _position;
    _sprite.center = { _sprite.size.x/2, _sprite.size.y /2 };
    _sprite.source = {
        .x = 0,
        .y = 0,
        .width = _sprite.size.x,
        .height = _sprite.size.y,
    };
    _sprite.dest = {
        _sprite.position.x,
        _sprite.position.y,
        _sprite.size.x,
        _sprite.size.y  
    };
    _sprite.roataion = 0.0;
    _sprite.modulate = WHITE;
        
}

inline void LoadSprite(Sprite &_sprite, Texture2D _texture, Vector2 _position) {
    _sprite.texture = _texture;
    _sprite.size = {(float)_texture.width, (float)_texture.height};
    _sprite.position = _position;
     _sprite.center = {0,0};
    _sprite.source = {
        .x = 0,
        .y = 0,
        .width = _sprite.size.x,
        .height = _sprite.size.y,
    };
    _sprite.dest = {
        _sprite.position.x,
        _sprite.position.y,
        _sprite.size.x,
        _sprite.size.y  
    };
    _sprite.roataion = 0.0;
}

inline void ScaleSprite(Sprite &_sprite, Vector2 _scale) {
    _sprite.scale = _scale;
    _sprite.center = { abs((_sprite.size.x * _sprite.scale.x)) * 0.5f, abs((_sprite.size.y * _sprite.scale.y)) * 0.5f };
    _sprite.source = {
        .x = 0,
        .y = 0,
        .width = _sprite.size.x,
        .height = _sprite.size.y
    };
    _sprite.dest = {
        _sprite.position.x,
        _sprite.position.y,
        _sprite.size.x * _sprite.scale.x,
        _sprite.size.y * _sprite.scale.y  
    };
}

inline void DrawSprite(Sprite &_sprite) {
    DrawTexturePro(_sprite.texture, _sprite.source, _sprite.dest, _sprite.center, _sprite.roataion, _sprite.modulate );       
}