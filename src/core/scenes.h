#pragma once

#include "bacescene.h"

class TitleScene : public  BaseScene{
    public:
    TitleScene();

    SCENE_ID TickScene() override;
    void DrawScene() override;
    void DestroyScene() override;

    private:

    Texture2D logo;

};
class GameScene : public  BaseScene{
    public:
    GameScene();

    SCENE_ID TickScene() override;
    void DrawScene() override;
    void DestroyScene() override;

    private:
};