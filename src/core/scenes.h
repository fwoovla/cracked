#pragma once
#include "bacescene.h"
#include "sprite.h"
#include "entities.h"
#include "ships.h"



class SplashScreen : public  BaseScene, public SignalObserver {
    public:
    SplashScreen();
    ~SplashScreen() override;
    SCENE_ID Update() override;
    void Draw() override;
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
    ~TitleScene() override;
    SCENE_ID Update() override;
    void Draw() override;
    void OnSignal(SIGNAL signal);

    BaseUILayer *ui;
    Button play_button;
    Sprite logo;
    Texture2D bg_texture;
    //gameSettings &game_settings;

};


class GameScene : public  BaseScene, public SignalObserver {
    public:
    GameScene(char level_data[]);
    ~GameScene() override;
    SCENE_ID Update() override;
    void Draw() override;
    void OnSignal(SIGNAL signal);
    void DrawLevel();
    void DrawDebug();



    BaseUILayer *ui;
    Camera2D camera;

    //int* level_array;
    PlayerShip *this_player;
    Texture space_tile_texture;
    Texture2D asteroid_texture;
    Texture2D bg_texture;

};


