#pragma once
//#include "global_def.h"
#include "baseuilayer.h"
#include "button.h"

class TitleUiLayer : public BaseUILayer {

    public:
    TitleUiLayer();
    ~TitleUiLayer() override;
    void Update() override;
    void Draw() override;

    private:
    Button start_button;
    Button quit_button;

};

class GameUILayer : public BaseUILayer {

    public:
    GameUILayer();
    ~GameUILayer() override;
    void Update() override;
    void Draw() override;
    
    private:
    
    Button quit_button;

};