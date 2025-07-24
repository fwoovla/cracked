#include "../../core/scenes.h"

GameScene::GameScene(char level_data[]) {
    scene_id = GAME_SCENE;
    return_scene = NO_SCENE;
    
//LOAD LEVEL------------------------------
    space_tile_texture = LoadTexture("assets/spacetile1.png");
    asteroid_texture = LoadTexture("assets/asteroid1.png");
    bg_texture = LoadTexture("assets/levelbg1.png");
    
    Image level_image = LoadImage(level_data);
    TraceLog(LOG_INFO, "LEVEL DATA LOADED, %s", level_data);   
    
    Color *colors = LoadImageColors(level_image);

    level_array = new int[LEVEL_SIZE * LEVEL_SIZE];

     for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
/*             Sprite new_tile;
            LoadSprite(new_tile, space_tile_texture, {(float)x *TILE_SIZE, (float)y *TILE_SIZE} );
            background_sprites.push_back(new_tile);  */
            if(colors[y * level_image.width + x].r == 255) {
                level_array[y * level_image.width + x] = 1;
            }
            else if (colors[y * level_image.width + x].r == 0) {
                level_array[y * level_image.width + x] = 0;
            }
        }
            
    } 

    UnloadImage(level_image);
    //LoadSprite(space_tile, space_tile_texture,);
//-----------------------------------------------

//LOAD UI----------------------------------------------
    ui = new GameUILayer();
    ui->ConnectSignalTo(this);

//LOAD PLAYER------------------------------------
    this_player = new PlayerShip( { (float)GetScreenWidth()/2 , (float)GetScreenHeight()/2} );
    this_player->camera = &camera;
    //TraceLog(LOG_INFO, "PLAYER CREATED");

//SETUP CAMERA--------------------------------------
    camera = { 0 };
    camera.target = (Vector2){ this_player->collision_rect.x, this_player->collision_rect.y};
    camera.offset = (Vector2){ this_player->position.x, this_player->position.y };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}


SCENE_ID GameScene::Update() {
    //TraceLog(LOG_INFO, "UPDATE GAME SCENE");
    if(IsKeyPressed(KEY_TAB)) {
        settings.show_debug = !settings.show_debug;
    }

    ui->Update();
    this_player->Update(level_array);

    camera.target = (Vector2){this_player->collision_rect.x, this_player->collision_rect.y};
    //camera.offset = (Vector2){ this_player->position.x, this_player->position.y };
    return return_scene;
}

void GameScene::Draw() {
    //TraceLog(LOG_INFO, "DRAW GAMESCEME");
    ClearBackground(BLACK);
    
    DrawTexturePro(bg_texture, {0,0,(float)bg_texture.width,(float)bg_texture.height}, {0,0,(float)GetScreenWidth(),(float)GetScreenHeight()}, {0}, 0.0,WHITE);

    BeginMode2D(camera);

    DrawLevel();

    if(settings.show_debug) {
        DrawDebug();
    }

    this_player->Draw();
    
    EndMode2D();
    
    ui->Draw();
}

void GameScene::Destroy() {
    delete[] level_array;
    delete this_player;
    UnloadTexture(space_tile_texture);
    UnloadTexture(asteroid_texture);
    UnloadTexture(bg_texture);
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

void GameScene::DrawLevel() {
    for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
            DrawTexture(space_tile_texture, x*TILE_SIZE, y*TILE_SIZE, WHITE);

            if(level_array[y * LEVEL_SIZE + x] == 0) {
                DrawTexture(asteroid_texture, x*TILE_SIZE, y*TILE_SIZE, WHITE);
                //DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, GOLD);
            }
        }
    }
}

void GameScene::DrawDebug() {
    if(settings.show_debug){
        for(int x = -1; x <  COLLISION_RANGE; x++) {
            for(int y = -1; y < COLLISION_RANGE; y++) {

                float fx = this_player->collision_rect.x + (TILE_SIZE + x);
                float fy = this_player->collision_rect.y + (TILE_SIZE + y);
                int ix = (this_player->collision_rect.x/TILE_SIZE) + x;
                int iy = (this_player->collision_rect.y/TILE_SIZE) + y;

                if(level_array[(iy) * LEVEL_SIZE + (ix)] == 0) {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, PINK);
                }
                else {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, BLUE);
                }
            }
        }
    }
}