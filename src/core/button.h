#pragma once
#include "../utils/utils.h"

struct Button {
    Vector2 position;
    Vector2 size;
    Vector2 center;
    Rectangle rect;
    Color focus_color;
    Color default_color;
    bool hovered;
    bool clicked;
    Signal button_pressed;
};

inline void CreateButton(Button &_button, Vector2 _position, Vector2 _size, Color _focus_color) {
    _button.focus_color = _focus_color;
    _button.default_color = GRAY;
    _button.size = _size;
    _button.hovered = false;
    _button.clicked = false;
    _button.position = {_position.x -( _button.size.x/2), _position.y - (_button.size.y/2) };
    _button.rect = { _button.position.x, _button.position.y, _button.size.x, _button.size.y};
}


inline void DrawButton(Button &_button) {
    if(_button.hovered) {
        DrawRectangleRec(_button.rect, _button.focus_color);
    }
    else {
        DrawRectangleRec(_button.rect, _button.default_color);
    }
}

inline bool IsButtonHovered(Button &_button) {
    if(CheckCollisionPointRec(GetMousePosition(), _button.rect)) {
        _button.hovered = true;
        return true;
    }
    _button.hovered = false;
    return false;
}