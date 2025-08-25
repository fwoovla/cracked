#pragma once
#include "ships.h"
#include "baseuilayer.h"
#include "global_def.h"

enum SHIPLOCATIONS {
    NONE,
    THRUSTERS,
    MAIN_GUN,
};


 class GameMenu : public BaseUILayer {

    public:
    GameMenu();
    ~GameMenu() override;
    void Update() override;
    void Draw() override;
    
    Vector2 screen_center;
    
    Button exit_button;
    Signal exit;

    Button continue_button;
    Signal reset;

    Sound button_sound;

    AnimatedPanel menu_panel;
};

 class PartsMenu : public BaseUILayer {

    public:
    PartsMenu();
    ~PartsMenu() override;
    void Update() override;
    void Draw() override;
    void DrawMainGunPurchaseStats(int index);
    void DrawThrusterPurchaseStats(int index);
        void DrawMainGunStats(int index);
    void DrawThrusterStats(int index);
    //void DrawMainGunPurchaseStats(int index);
    
    Vector2 screen_center;
    
    Button part_exit_button;

    Button exit_button;
    Signal parts_close;
    AnimatedPanel menu_panel;

    Label header;

    Sprite ship_outline_sprite;
    Sprite engine_outline_sprite;
    Sprite gun_outline_sprite;

    SHIPLOCATIONS selected_location;
    SHIPLOCATIONS hovered_location;

    Rectangle engine_area;
    Rectangle gun_area;

    Label equipped_part_header;
    Label equipped_part_label;

    LabelList equipped_part_stat_list;

    Label shop_header;
    Vector2 ppasp; //purchase part area start position
    std::vector<Rectangle> purchase_part_areas;

    Panel part_detail_panel;
    Button part_buy_button;

    int hovered_purchase_part_index;
    int selected_purchase_part_index;

    Sound button_sound;
};

 class ShipyardMenu : public BaseUILayer {

    public:
    ShipyardMenu();
    ~ShipyardMenu() override;
    void Update() override;
    void Draw() override;
    
    Vector2 screen_center;
    
    Button exit_button;
    Signal exit;

    Signal shipyard_close;

    Rectangle gun_power_rect;
    Color gun_power_color;

    AnimatedPanel menu_panel;
    Label header;
    
    Sound button_sound;

};

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

    AnimatedPanel menu_panel;
    
};


class StagingUILayer : public BaseUILayer {

    public:
    StagingUILayer();
    ~StagingUILayer() override;
    
    void Update() override;
    void Draw() override;

    void ShowShopPanel();
    void ShowBattlePanel();
    void HideShopPanel();
    void HideBattlePanel();
    void DrawShopPanel();
    void UpdateShopPanel();
    void DrawBattlePanel();
    void UpdateBattlePanel();
    void OnPartsClosed();
    void OnShipyardClosed();

    PartsMenu parts_menu;
    ShipyardMenu shipyard_menu;

    Button quit_button;
    Signal quit_pressed;

    Sound button_sound;
    Vector2 screen_center;

    Rectangle top_bar_rect;
    Label scrap_label;

    Panel battle_panel;
    Button battle_button;
    Signal battle_pressed;

    Panel shop_panel;
    Button parts_button;
    Button shipyard_button;
    Signal parts_pressed;
    Signal shipyard_pressed;



    bool shop_panel_visible;
    bool battle_panel_visible;
    bool parts_visible;
    bool shipyard_visible;
    bool menus_are_open;
};


class GameUILayer : public BaseUILayer {

    public:
    GameUILayer();
    ~GameUILayer() override;
    void Update() override;
    void Draw() override;
    void OnPlayerShoot();
    void OnPlayerHit();
    void OnPlayerPickedUpScrap();
    void OnHitEffectTimeout();
    void OnPlayerKilledEnemy();
    void OnCountdownTimerTimeout();
    void StartCountdown();
    
    int countdown_time;
    Label countdown_label;
    Timer *countdown_timer;
    float countdown_fade;
    Signal countdown_over;

    Label points_tag_label;
    Label points_value_label;

    Label scrap_tag_label;
    Label scrap_value_label;

    Label int_time_value_label;
    Label float_time_value_label;

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
    bool animating_scrap;

    float _game_time;

    Sound beep;
    Sound long_beep;

};

