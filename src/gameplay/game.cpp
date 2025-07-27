#include "../core/game.h"


Game::Game(){
    TraceLog(LOG_INFO, "GAME-- SETTINGS,%i  %f, %f", settings.show_debug, settings.window_size.x, settings.window_size.y);

    running = false;
    scene_manager = new SceneManager;
    
}

Game::~Game() {
    delete scene_manager;

}

void Game::StartGame() {
    running = true;

    while(running) {

        scene_manager->UpdateScene();
        
        BeginDrawing();
        scene_manager->DrawScene();
        //ClearBackground(RAYWHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_ESCAPE)) {
            running = false;
        }
    }
}


