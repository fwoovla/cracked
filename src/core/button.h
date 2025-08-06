#pragma once
#include "../utils/utils.h"
#include <string>

struct Button {
    Vector2 position;
    Vector2 size;
    Vector2 center;
    Rectangle rect;
    Color focus_color;
    Color default_color;
    std::string text;
    int text_size;
    bool hovered;
    bool already_hovered;
    bool clicked;
    Signal button_pressed;
};

inline void CreateButton(Button &_button, Vector2 _position, Vector2 _size, Color _focus_color, std::string _text) {
    _button.focus_color = _focus_color;
    _button.default_color = GRAY;
    _button.size = _size;
    _button.hovered = false;
    _button.already_hovered = false;
    _button.clicked = false;
    _button.position = _position;
    _button.rect = { _position.x -( _button.size.x/2), _position.y - (_button.size.y/2), _button.size.x, _button.size.y};
    _button.text_size = 30;
    _button.text = _text;
}


inline void DrawButton(Button &_button) {
    if(_button.hovered) {
        DrawRectangleRec(_button.rect, _button.focus_color);

        int tw = MeasureText(_button.text.c_str(), _button.text_size);
        DrawText((TextFormat("%s",_button.text.c_str())), _button.position.x - (tw *0.5), _button.position.y - (_button.text_size *0.5f), _button.text_size, DARKGRAY);
        //TraceLog(LOG_INFO, "BUTTON TEXT %s", _button.text.c_str());
    }
    else {
        DrawRectangleRec(_button.rect, _button.default_color);

        int tw = MeasureText(_button.text.c_str(), _button.text_size);
        DrawText((TextFormat("%s",_button.text.c_str())), _button.position.x - (tw*0.5), _button.position.y - (_button.text_size *0.5f), _button.text_size, RAYWHITE);
    }
}

inline bool IsButtonHovered(Button &_button) {
    _button.already_hovered = _button.hovered;
    if(CheckCollisionPointRec(GetMousePosition(), _button.rect)) {
        _button.hovered = true;
        return true;
    }
    _button.hovered = false;
    return false;
}