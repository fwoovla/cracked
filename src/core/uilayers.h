#pragma once
#include "ships.h"
#include "baseuilayer.h"
#include "button.h"
#include "label.h"

class TitleUiLayer : public BaseUILayer {

    public:
    TitleUiLayer();
    ~TitleUiLayer() override;
    
    void Update() override;
    void Draw() override;

    Button start_button;
    Button settings_button;
    Button quit_button;
    Signal play_pressed;
    Signal quit_pressed;

    Sound button_sound;
    Vector2 screen_center;
    
};

class GameUILayer : public BaseUILayer {

    public:
    GameUILayer();
    ~GameUILayer() override;
    void Update() override;
    void Draw() override;
    void OnPlayerShoot();
    void OnPlayerHit();
    void OnHitEffectTimeout();
    void OnPlayerKilledEnemy();
    
    
    Label points_tag_label;
    Label points_value_label;

    Button quit_button;
    Signal quit_pressed;

    PlayerShip *player;

    Rectangle gun_power_rect;
    Color gun_power_color;

    Sound button_sound;

    Timer *hit_effect_timer;
    float hit_effect_alpha_value;
    float hit_effect_alpha_step;
    bool show_hit_effect;

    bool animating_points;

};

 class GameMenu : public BaseUILayer {

    public:
    GameMenu();
    ~GameMenu() override;
    void Update() override;
    void Draw() override;
    void OnPlayerShoot();
    
    
    Button exit_button;
    Signal exit;

    Button continue_button;
    Signal reset;

    Rectangle gun_power_rect;
    Color gun_power_color;

    Sound button_sound;
};