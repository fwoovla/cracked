#include "../core/game.h"


Game::Game(){
    TraceLog(LOG_INFO, "GAME-- SETTINGS,%i  %f, %f", settings.show_debug, settings.window_size.x, settings.window_size.y);

    running = false;
    scene_manager = new SceneManager;
    render_texture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    //render_texture = LoadRenderTexture(800, 800);
}

Game::~Game() {
    delete scene_manager;
}

void Game::StartGame() {
    running = true;

    while(running) {

        scene_manager->UpdateScene();
        
        //draw everything to the render texture
        BeginTextureMode(render_texture);
        scene_manager->DrawScene();
        EndTextureMode();

        //do render stuff
        BeginDrawing();
        DrawTextureRec(render_texture.texture, {0,0,(float)render_texture.texture.width,-(float)render_texture.texture.height}, {0,0}, WHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_ESCAPE)) {
            running = false;
        }
    }
}


