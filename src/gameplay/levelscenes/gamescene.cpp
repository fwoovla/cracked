#include "../../core/scenes.h"

GameScene::GameScene() {
    scene_id = GAME_SCENE;

}


SCENE_ID GameScene::Update()
{

    return NO_SCENE;

}

void GameScene::Draw() {
    ClearBackground(GOLD);
    DrawText("GAME SCENE", 200, 200, 40, BLACK);
}
void GameScene::Destroy() {

}

void GameScene::OnSignal(SIGNAL signal) {

}