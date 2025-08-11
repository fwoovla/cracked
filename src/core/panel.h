#pragma once
#include "../utils/utils.h"
#include <string>

struct Panel {
    std::string text;
    Vector2 position;
    Color default_color;
    Vector2 size;
};

struct AnimatedPanel : public Panel {
    int mid_h;
    float step;
    float ball_radius;
    float animation_time;
    float last_frame_time;
    Vector2 ball1;
    Vector2 ball2;
    Vector2 ball3;
    Vector2 ball4;
    bool animating;

    std::vector<Vector2> points1;
    std::vector<Vector2> points2;
    std::vector<Vector2> points3;
    std::vector<Vector2> points4;
};


inline void CreatePanel(Panel &_panel, Vector2 _position, Vector2 _size, Color _default_color) {
    _panel.position = _position;
    _panel.size = _size;
    _panel.default_color = _default_color;
}

inline void CreatePanel(AnimatedPanel &_panel, Vector2 _position, Vector2 _size, Color _default_color, float _time) {
    _panel.position = _position;
    _panel.size = _size;
    _panel.default_color = _default_color;
    _panel.animation_time = _time;
    _panel.step = 10.0f;

    _panel.ball1 = {_position.x + (_size.x *0.5f), _position.y - 10};
    _panel.ball2 = {_position.x + (_size.x *0.5f), _position.y + _size.y + 10};

    _panel.ball3 = {_position.x + (_size.x *0.5f), _position.y - 10};
    _panel.ball4 = {_position.x + (_size.x *0.5f), _position.y + _size.y + 10};

    _panel.ball_radius = 10;
    _panel.animating = true;
    
    _panel.points1.clear();
    _panel.points1.push_back(_panel.ball1);

    _panel.points2.clear();
    _panel.points2.push_back(_panel.ball2);

    _panel.points3.clear();
    _panel.points3.push_back(_panel.ball3);

    _panel.points4.clear();
    _panel.points4.push_back(_panel.ball4);
}

inline void DrawPanel(Panel &_panel) {
    DrawRectangleV(_panel.position, _panel.size, _panel.default_color);
}

inline void DrawPanel(AnimatedPanel &_panel) {
    DrawRectangleV(_panel.position, _panel.size, _panel.default_color);

    DrawCircleV({_panel.ball1.x, _panel.ball1.y}, _panel.ball_radius, GOLD);
    DrawCircleV({_panel.ball2.x, _panel.ball2.y}, _panel.ball_radius, GOLD);


    DrawCircleV({_panel.ball3.x, _panel.ball3.y}, _panel.ball_radius, GOLD);
    DrawCircleV({_panel.ball4.x, _panel.ball4.y}, _panel.ball_radius, GOLD);

    if(_panel.points1.size() > 1) {
        for(int i = 0; i+1 < _panel.points1.size(); i++) {
            DrawLineV(_panel.points1[i], _panel.points1[i+1], WHITE);
        }
    }
    if(_panel.points2.size() > 1) {
        for(int i = 0; i+1 < _panel.points2.size(); i++) {
            DrawLineV(_panel.points2[i], _panel.points2[i+1], WHITE);
        }
    }
    if(_panel.points3.size() > 1) {
        for(int i = 0; i+1 < _panel.points3.size(); i++) {
            DrawLineV(_panel.points3[i], _panel.points3[i+1], WHITE);
        }
    }
    if(_panel.points4.size() > 1) {
        for(int i = 0; i+1 < _panel.points4.size(); i++) {
            DrawLineV(_panel.points4[i], _panel.points4[i+1], WHITE);
        }
    }
}

inline void UpdatePanel(Panel &_panel) {

}

inline void UpdatePanel(AnimatedPanel &_panel) {
    if(!_panel.animating) {
        return;
    }

    if(_panel.ball1.x > _panel.position.x - 10) {
        _panel.ball1.x -= _panel.step;
        _panel.points1.push_back(_panel.ball1);

        _panel.ball2.x -= _panel.step;
        _panel.points2.push_back(_panel.ball2);
    }
    else if (_panel.ball1.x <= _panel.position.x - 10)
     {
        _panel.ball1.y += _panel.step;
        _panel.points1.push_back(_panel.ball1);

        _panel.ball2.y -= _panel.step;
        _panel.points2.push_back(_panel.ball2);
    }

    if(_panel.ball3.x <  _panel.position.x +_panel.size.x + 10) {
        _panel.ball3.x += _panel.step;
        _panel.points3.push_back(_panel.ball3);

        _panel.ball4.x += _panel.step;
        _panel.points4.push_back(_panel.ball4);
    }
    else if (_panel.ball3.x >=  _panel.position.x +_panel.size.x + 10)
     {
        _panel.ball3.y += _panel.step;
        _panel.points3.push_back(_panel.ball3);

        _panel.ball4.y -= _panel.step;
        _panel.points4.push_back(_panel.ball4);
    }

     if (_panel.ball1.y > _panel.position.y + 200) {
        _panel.animating = false;
    }
}