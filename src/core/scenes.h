#pragma once

//#include "global_def.h"


#include "bacescene.h"
#include "sprite.h"
#include "uilayers.h"
#include "../utils/utils.h"
/* 
#include "entities.h"
#include "ships.h"
 */


class SplashScreen : public  BaseScene{
    public:
    SplashScreen();
    ~SplashScreen() override;
    SCENE_ID Update() override;
    void Draw() override;
    void OnSignal();


    Timer *timer;
    float alpha_value;
    float alpha_step;
    Sprite logo;
    //gameSettings &game_settings;

};


class TitleScene : public  BaseScene{
    public:
    TitleScene();
    ~TitleScene() override;
    SCENE_ID Update() override;
    void Draw() override;
    void OnPlayPressed();
    void OnQuitPressed();
    void OnFadeOut();

    TitleUiLayer *ui;
    //Button play_button;
    Sprite logo;
    Texture2D bg_texture;
    //gameSettings &game_settings;
    Timer *fade_timer;
    float alpha_value;
    float alpha_step;
    bool transitioning;

    Music bg_music;

};


class StagingScene : public  BaseScene{
    public:
    StagingScene();
    ~StagingScene() override;
    SCENE_ID Update() override;
    void Draw() override;
    void OnPlayPressed();
    void OnQuitPressed();
    void OnFadeOut();

    StagingUILayer *ui;
    //Button play_button;
    //Sprite logo;
    Texture2D bg_texture;
    //gameSettings &game_settings;
    Timer *fade_timer;
    float alpha_value;
    float alpha_step;
    bool transitioning;

    AnimatedSprite door_light;

    Rectangle shop_area;
    Rectangle battle_area;

    Music bg_music;

};


class GameScene : public  BaseScene{
    public:
    GameScene(char level_data[]);
    ~GameScene() override;
    SCENE_ID Update() override;
    void Draw() override;

    void DrawLevel();
    void DrawDebug();
    void OnQuitPressed();
    void OnHealthPickedUp();
    void OnPlayerPickedUpScrap();
    void OnEnemySpawnTimerTimeout();
    void OnCountdownTimeout();
    void OnEnemyDead();
    void OnPlayerKilledEnemy();
    void OnPlayerDead();
    void OnMenuExit();
    void OnMenuRestart();
    void ClearEntitiesExceptPlayer();

    GameUILayer *ui;
    Camera2D camera;

    //int* level_array;
    PlayerShip *this_player;
    Texture space_tile_texture;
    Texture2D asteroid_texture;
    Texture2D bg_texture;
    std::vector<Vector2> pickup_positions;
    std::vector<Vector2> enemy_positions;

    Timer *enemy_spawn_timer;
    int spawned_enemy_amount;

    GameMenu *menu;

    bool show_menu;

    Sound enemy_explosion_sound;
    Sound game_over_sound;
    Sound pickup_sound;

    Music bg_music;

    //Timer *game_timer;
    bool time_running;
    float game_time;
};


