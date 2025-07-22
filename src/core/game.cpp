#include "game.h"


Game::Game(gameSettings &_game_settings){
    game_settings = _game_settings;
    running = false;
    scene_manager = new SceneManager();
    
    
}

Game::~Game() {

}

void Game::StartGame() {



    running = true;


    while(running) {

        
        scene_manager->UpdateScene();
        scene_manager->DrawScene();

        BeginDrawing();
        //ClearBackground(RAYWHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_ESCAPE)) {
            running = false;
        }
        if(IsKeyPressed(KEY_SPACE)) {
            if(scene_manager->current_scene->scene_id == TITLE_SCENE) {
                scene_manager->ChangeSceneTo(GAME_SCENE);
            }
            else if(scene_manager->current_scene->scene_id == GAME_SCENE) {
                scene_manager->ChangeSceneTo(TITLE_SCENE);
            }
        }
    }
}


