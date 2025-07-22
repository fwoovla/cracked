#include "scenemanager.h"

SceneManager::SceneManager() {
    //g_scenemanager = this;
    current_scene = new TitleScene();
    
}

void SceneManager::UpdateScene() {
    if(current_scene == nullptr){
        return;
    }
    SCENE_ID new_scene = NO_SCENE;
    
    new_scene = current_scene->Update();
    switch (new_scene) {
        case NO_SCENE:
            break;

        default:
            ChangeSceneTo(new_scene);
    }

}

void SceneManager::DrawScene() {
    current_scene->Draw();

}

void SceneManager::ChangeSceneTo(SCENE_ID new_scene) {
    
    current_scene->Destroy();
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

