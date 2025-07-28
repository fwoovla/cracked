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

    TitleUiLayer *ui;
    //Button play_button;
    Sprite logo;
    Texture2D bg_texture;
    //gameSettings &game_settings;

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



    GameUILayer*ui;
    Camera2D camera;

    //int* level_array;
    PlayerShip *this_player;
    Texture space_tile_texture;
    Texture2D asteroid_texture;
    Texture2D bg_texture;

};


