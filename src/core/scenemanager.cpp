#include "scenemanager.h"

SceneManager::SceneManager() {
    current_scene = new TitleScene();
}

void SceneManager::UpdateScene() {
    if(current_scene == nullptr){
        return;
    }
    SCENE_ID new_scene = NO_SCENE;
    
    new_scene = current_scene->TickScene();
    switch (new_scene) {
        case NO_SCENE:
            break;
    
        case TITLE_SCENE:
            ChangeSceneTo(new_scene);

        default:
            break;
    }

}

void SceneManager::DrawScene() {
    current_scene->DrawScene();

}

void SceneManager::ChangeSceneTo(SCENE_ID new_scene) {
    delete(current_scene);

    switch (new_scene) {
        case TITLE_SCENE:
            current_scene = new TitleScene();
            break;
    
        case GAME_SCENE:
            current_scene = new GameScene();
            break;

        default:
            break;
    }

}
