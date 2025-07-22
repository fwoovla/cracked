#include "../../core/scenes.h"
#include "../../core/sprite.h"
#include "../../core/button.h"

#include "../../utils/utils.h"

TitleScene::TitleScene(){
    scene_id = TITLE_SCENE;
    return_scene = NO_SCENE;

    Vector2 screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    LoadSpriteCentered(logo, LoadTexture("assets/logo_pic_large.png"), screen_center);
    ScaleSprite(logo, {2,2});

    ui = new TitleUiLayer();
    ui->ConnectSignalTo(this);

}


SCENE_ID TitleScene::Update() {
    ui->Update();

    if(IsKeyPressed(KEY_ENTER)) {
        return_scene = GAME_SCENE;
    }
    return return_scene;
}

void TitleScene::Draw() {
    ClearBackground(BLUE);
    DrawSprite(logo);
    ui->Draw();
    //DrawButton(play_button);
    DrawText("TITLE SCENE", 200, 200, 40, BLACK);
    DrawText("X", (float)GetScreenWidth()/2, (float)GetScreenHeight() /2, 10, BLACK);
}

void TitleScene::Destroy() {
    TraceLog(LOG_INFO, "DESTROY TITLE");
    UnloadTexture(logo.texture);
    delete ui;
}

void TitleScene::OnSignal(SIGNAL signal) {
    TraceLog(LOG_INFO, "SCENE KNOWS");
    switch (signal)
    {
    case GAME_SCENE:
        return_scene = GAME_SCENE;
        break;

    case END_GAME:
        
        return_scene = TITLE_SCENE;
        break;
    default:
        break;
    }
}