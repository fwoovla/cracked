#pragma once
#include "ships.h"
#include "baseuilayer.h"
#include "button.h"

class TitleUiLayer : public BaseUILayer {

    public:
    TitleUiLayer();
    ~TitleUiLayer() override;
    void Update() override;
    void Draw() override;

    Button start_button;
    Button quit_button;
    Signal play_pressed;
    Signal quit_pressed;
    
    private:

};

class GameUILayer : public BaseUILayer {

    public:
    GameUILayer();
    ~GameUILayer() override;
    void Update() override;
    void Draw() override;
    void OnPlayerShoot();
    
    
    Button quit_button;
    Signal quit_pressed;

    PlayerShip *player;
    private:

};