#include "../../core/scenes.h"

GameScene::GameScene(char level_data[]) {
    scene_id = GAME_SCENE;
    return_scene = NO_SCENE;
    
//LOAD LEVEL------------------------------
    
    Image level_image = LoadImage(level_data);
    TraceLog(LOG_INFO, "LEVEL DATA LOADED, %s", level_data);   
    
    Color *colors = LoadImageColors(level_image);

    level_array = new int[LEVEL_SIZE * LEVEL_SIZE];

     for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
            if(colors[y * level_image.width + x].r == 255) {
                level_array[y * level_image.width + x] = 1;
            }
            else if (colors[y * level_image.width + x].r == 0) {
                level_array[y * level_image.width + x] = 0;
            }
        }
    } 

    UnloadImage(level_image);
//-----------------------------------------------

//LOAD UI----------------------------------------------
    ui = new GameUILayer();
    ui->ConnectSignalTo(this);

//LOAD PLAYER------------------------------------
    this_player = new Player();
    TraceLog(LOG_INFO, "PLAYER CREATED");

    player = { 32*TILE_SIZE, 32 *TILE_SIZE, PLAYER_SIZE, PLAYER_SIZE };

//SETUP CAMERA--------------------------------------
    camera = { 0 };
    camera.target = (Vector2){ player.x, player.y};
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;
}


SCENE_ID GameScene::Update() {
    //TraceLog(LOG_INFO, "UPDATE GAME SCENE");
    float dt = GetFrameTime();
    ui->Update();
    
    
    player_collided = false;
    Vector2 previous_position = {player.x, player.y};
    
    if (IsKeyDown(KEY_D)) player.x += PLAYER_SPEED * dt;
    else if (IsKeyDown(KEY_A)) player.x -= PLAYER_SPEED * dt;
            
    if (IsKeyDown(KEY_W)) player.y -= PLAYER_SPEED * dt;
    else if (IsKeyDown(KEY_S)) player.y += PLAYER_SPEED * dt;
    
    if(!player_collided) {
    
        for(int x = -1; x <  2; x++) {
            for(int y = -1; y < 2; y++) {

                float fx = player.x + (TILE_SIZE + x);
                float fy = player.y + (TILE_SIZE + y);
                int ix = (player.x/TILE_SIZE) + x;
                int iy = (player.y/TILE_SIZE) + y;

                if(level_array[(iy * LEVEL_SIZE + ix)] == 0) {
                    //DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, PINK);

                    TraceLog(LOG_INFO, "checking %i ", level_array[(y + iy) * LEVEL_SIZE + (x + ix)]);
                    TraceLog(LOG_INFO, "checking cell at FLOAT %f %f ", fx, fy);
                    TraceLog(LOG_INFO, "checking cell at index%i %i ", ix, iy);
                    TraceLog(LOG_INFO, "checking rect at FLOAT %f %f \n", (float)ix * TILE_SIZE, (float)iy * TILE_SIZE);

                    if(CheckCollisionRecs( {player.x,player.y, PLAYER_SIZE, PLAYER_SIZE}, {(float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE, TILE_SIZE} )) {
                        player_collided = true;
                        TraceLog(LOG_INFO, "COLLISION");
                    }
                    else {
                        TraceLog(LOG_INFO, "NO COLLISION");
                    }
                }

            }
        }
    }
    
    if(player_collided) {
        player.x = previous_position.x;
        player.y = previous_position.y;
    }
    camera.target = (Vector2){ player.x, player.y};
    //return NO_SCENE;
    return return_scene;

}

void GameScene::Draw() {
    //TraceLog(LOG_INFO, "DRAW GAMESCEME");
    ClearBackground(BLACK);
    
    
    BeginMode2D(camera);

    for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
            //TraceLog(LOG_INFO, "drawing %i ", level_array[y * LEVEL_SIZE + x]);
            if(level_array[y * LEVEL_SIZE + x] == 0) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GOLD);
            }
        }
    }
    if(settings.show_debug){
        for(int x = -1; x <  2; x++) {
            for(int y = -1; y < 2; y++) {

                float fx = player.x + (TILE_SIZE + x);
                float fy = player.y + (TILE_SIZE + y);
                int ix = (player.x/TILE_SIZE) + x;
                int iy = (player.y/TILE_SIZE) + y;

                if(level_array[(iy) * LEVEL_SIZE + (ix)] == 0) {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, PINK);
                }
                else {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, BLUE);
                }
            }
        }
    }
    this_player->Draw();
    if(player_collided) {
        DrawRectangleRec(player, RED);
    }
    else {
        DrawRectangleRec(player, GREEN);
    }
    //DrawRectangle(player.x, player.y, PLAYER_SIZE,PLAYER_SIZE, PINK);

    EndMode2D();

    ui->Draw();
}

void GameScene::Destroy() {
    //UnloadImage(level_image);
}

void GameScene::OnSignal(SIGNAL signal) {

    TraceLog(LOG_INFO, "SCENE KNOWS, %i", signal);
    switch (signal)
    {
    case END_GAME:
        return_scene = SPLASH_SCENE;
        break;

    default:
        TraceLog(LOG_INFO, "SCENE DOES NOT KNOW, %i", signal);
        break;
    }
}
