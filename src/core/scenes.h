#pragma once
#include "bacescene.h"
#include "sprite.h"

class TitleScene : public  BaseScene, public SignalObserver {
    public:
    TitleScene();
    SCENE_ID Update() override;
    void Draw() override;
    void Destroy() override;
    void OnSignal(SIGNAL signal);

    Sprite logo;
    BaseUILayer *ui;
    Button play_button;
};


class GameScene : public  BaseScene, public SignalObserver {
    public:
    GameScene();
    SCENE_ID Update() override;
    void Draw() override;
    void Destroy() override;
    void OnSignal(SIGNAL signal);


    //Timer timer;

};