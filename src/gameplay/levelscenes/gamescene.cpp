#include "../../core/scenes.h"

GameScene::GameScene() {
    scene_id = GAME_SCENE;
}

SCENE_ID GameScene::TickScene() {
    return NO_SCENE;
}

void GameScene::DestroyScene() {
    TraceLog(LOG_INFO, "GAME SCENE DESTROYED");

}

void GameScene::DrawScene() {
    ClearBackground(GOLD);
    DrawText("GAME SCENE", 200, 200, 40, BLACK);
}