#pragma once
#include "../utils/utils.h"
#include <string>

struct Label {
    std::string text;
    Vector2 position;
    Color default_color;
    std::string text;
    int text_size;
};

inline void CreateLabel(Label &_label, Vector2 _position, Vector2 _size, Color _default_color, std::string _text) {
    _label.default_color = _default_color;
    _label.position = _position;
    _label.text_size = 30;
    _label.text = _text;
}

inline void DrawLabel(Label &_label) {

    int tw = MeasureText(_label.text.c_str(), _label.text_size);
    DrawText((TextFormat("%s",_label.text.c_str())), _label.position.x - (tw*0.5), _label.position.y - (_label.text_size *0.5f), _label.text_size, _label.default_color);
}