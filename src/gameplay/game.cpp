#include "../core/global_def.h"
bool game_running;
PlayerData player_data;

std::unordered_map<int, PartMainGun> main_gun_data;
std::unordered_map<int, PartThrusters> thrusters_data;
std::unordered_map<int, PartArmor> armors_data;


Game::Game(){
    TraceLog(LOG_INFO, "GAME-- SETTINGS, %i  %f, %f", settings.show_debug, settings.window_size.x, settings.window_size.y);
    game_running = false;
    scene_manager = new SceneManager;
    render_texture = LoadRenderTexture(settings.resolution.x, settings.resolution.y);
    
    LoadGameData();
    InitPlayerShip(player_data);
}

Game::~Game() {
    delete scene_manager;
}

void Game::StartGame() {
    
    game_running = true;
    
    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_BILINEAR);

    float scaleX = (float)GetScreenWidth() / settings.resolution.x;
    float scaleY = (float)GetScreenHeight() / settings.resolution.y;
    settings.game_scale = (scaleX < scaleY) ? scaleX : scaleY;  //behold the fancyness

    int offsetX = (GetScreenWidth() - (settings.resolution.x*settings.game_scale)) / 2;
    int offsetY = (GetScreenHeight() - (settings.resolution.y*settings.game_scale)) / 2;

    while(game_running) {

        scene_manager->UpdateScene();
        
        //draw everything to the render texture
        BeginTextureMode(render_texture);
        scene_manager->DrawScene();
        
        EndTextureMode();

        //do render stuff
        BeginDrawing();
        ClearBackground(BLACK);

        
        DrawTexturePro(
            render_texture.texture,
            (Rectangle){ 0, 0, (float)render_texture.texture.width, -(float)render_texture.texture.height },
            (Rectangle){ (float)offsetX, (float)offsetY, settings.resolution.x*settings.game_scale, settings.resolution.y*settings.game_scale },
            (Vector2){0, 0}, 0.0f, WHITE
        );
        
        //DrawTextureRec(render_texture.texture, {0,0,(float)render_texture.texture.width, -(float)render_texture.texture.height}, {0,0}, WHITE);
        EndDrawing();

        /* if(WindowShouldClose()) {
            game_running = false;
        } */
    }
}


