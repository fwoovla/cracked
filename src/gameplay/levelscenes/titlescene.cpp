#include "../../core/scenes.h"

TitleScene::TitleScene() {
    scene_id = TITLE_SCENE;

    logo = LoadTexture("assets/logo_pic_large.png");

}

SCENE_ID TitleScene::TickScene() {
    return NO_SCENE;
}

void TitleScene::DrawScene() {
    ClearBackground(BLUE);
    DrawText("TITLE SCENE", 200, 200, 40, BLACK);
}

void TitleScene::DestroyScene() {
    TraceLog(LOG_INFO, "TITLE SCENE DESTROYED");

}
