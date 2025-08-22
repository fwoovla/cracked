#include "../core/global_def.h"
bool game_running;
PlayerData player_data;

std::unordered_map<int, PartMainGun> main_gun_data;
std::unordered_map<int, PartThrusters> thrusters_data;


Game::Game(){
    TraceLog(LOG_INFO, "GAME-- SETTINGS, %i  %f, %f", settings.show_debug, settings.window_size.x, settings.window_size.y);
    game_running = false;
    scene_manager = new SceneManager;
    render_texture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    LoadGameData();
    InitPlayerShip(player_data);
}

Game::~Game() {
    delete scene_manager;
}

void Game::StartGame() {
    
    game_running = true;

    while(game_running) {

        scene_manager->UpdateScene();
        
        //draw everything to the render texture
        BeginTextureMode(render_texture);
        scene_manager->DrawScene();
        EndTextureMode();

        //do render stuff
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextureRec(render_texture.texture, {0,0,(float)render_texture.texture.width,-(float)render_texture.texture.height}, {0,0}, WHITE);
        EndDrawing();

        /* if(WindowShouldClose()) {
            game_running = false;
        } */
    }
}


