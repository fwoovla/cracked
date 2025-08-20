#pragma once
#include "../utils/utils.h"
#include "label.h"
#include <string>

struct LabelList {
    std::vector<std::string> label_texts;
    std::string header_text;
    Vector2 position;
    float h_size;
    Color label_color;
    Color border_color;
    int label_text_size;
    int header_text_size;
};

inline void CreateLabelList(LabelList &_list, Vector2 _position, float _h_size, int _lt_size, int _ht_size, Color _l_color, Color _b_color, std::string _h_text) {
    _list.label_texts.clear();
    _list.position = _position;
    _list.h_size = _h_size;
    _list.label_text_size = _lt_size;
    _list.header_text_size = _ht_size;
    _list.label_color = _l_color;
    _list.border_color = _b_color;
    _list.header_text = _h_text;
}

inline void ClearLabelList(LabelList & _list) {
    _list.label_texts.clear();
    _list.header_text = "";
}

inline void AddLabelToList(LabelList &_list, std::string _text) {
    _list.label_texts.push_back(_text);
}

inline void DrawLabelList(LabelList &_list) {
    DrawText(TextFormat("%s",_list.header_text.c_str()), _list.position.x, _list.position.y - _list.header_text_size, _list.header_text_size, WHITE);

    //DrawRectangleLines(_list.position.x, _list.position.y, _list.h_size, (_list.label_texts.size() + 1) * _list.label_text_size, _list.border_color);
    DrawLine(   _list.position.x, _list.position.y,
                _list.position.x, _list.position.y + (_list.label_texts.size() * _list.label_text_size),
                _list.border_color
            );

    for(int i = 0; i < _list.label_texts.size(); i++) {
        DrawText(TextFormat("%s",_list.label_texts[i].c_str()), _list.position.x + 10, _list.position.y + (i*_list.label_text_size), _list.label_text_size, _list.label_color);
    }
}

