#pragma once
#include "bacescene.h"
#include "sprite.h"
#include "entities.h"
#include "ships.h"



class SplashScreen : public  BaseScene, public SignalObserver {
    public:
    SplashScreen();
    SCENE_ID Update() override;
    void Draw() override;
    void Destroy() override;
    void OnSignal(SIGNAL signal);


    Timer *timer;
    float alpha_value;
    float alpha_step;
    Sprite logo;
    //gameSettings &game_settings;

};


class TitleScene : public  BaseScene, public SignalObserver {
    public:
    TitleScene();
    SCENE_ID Update() override;
    void Draw() override;
    void Destroy() override;
    void OnSignal(SIGNAL signal);

    BaseUILayer *ui;
    Button play_button;
    Sprite logo;
    //gameSettings &game_settings;

};


class GameScene : public  BaseScene, public SignalObserver {
    public:
    GameScene(char level_data[]);
    SCENE_ID Update() override;
    void Draw() override;
    void Destroy() override;
    void OnSignal(SIGNAL signal);
    void DrawLevel();
    void DrawDebug();

    //Image *level_image;

    BaseUILayer *ui;
    Camera2D camera;
    //Rectangle player;

    int* level_array;
    //bool player_collided;
    PlayerShip *this_player;
    Texture space_tile_texture;
    Texture2D asteroid_texture;
    Texture2D bg_texture;
    //Sprite space_tile;
    //std::vector<Sprite > background_sprites;

};