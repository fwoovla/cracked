
#include "../../core/global_def.h"
#include <raymath.h>

int* level_array_data;

DrawableEntity *bullet_list[DRAW_LIST_SIZE] = {nullptr};
DrawableEntity *entity_list[DRAW_LIST_SIZE] = {nullptr};
DrawableEntity *effects_list[DRAW_LIST_SIZE] = {nullptr};
std::vector<DrawableEntity*> *collision_data[LEVEL_SIZE * LEVEL_SIZE] = {nullptr};


GameScene::GameScene(char level_data[]) {
    scene_id = GAME_SCENE;
    return_scene = NO_SCENE;
    //delete draw_list;

 
    for(int i = 0; i < LEVEL_SIZE*LEVEL_SIZE; i++) {
        if(collision_data[i] != nullptr) {
            collision_data[i]->clear();
        }
    }

    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        delete bullet_list[i];
        bullet_list[i] = nullptr;
         delete(entity_list[i]);
        entity_list[i] = nullptr; 
    } 
    
    
//LOAD LEVEL------------------------------
    space_tile_texture = LoadTexture("assets/spacetile1.png");
    asteroid_texture = LoadTexture("assets/asteroid1.png");
    bg_texture = LoadTexture("assets/levelbg1.png");
    
    Image level_image = LoadImage(level_data);
    TraceLog(LOG_INFO, "LEVEL DATA LOADED, %s", level_data); 
    
    Color *colors = LoadImageColors(level_image);

    level_array_data = new int[LEVEL_SIZE * LEVEL_SIZE];

     for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
            if(colors[y * level_image.width + x].r == 255) {
                level_array_data[y * level_image.width + x] = 1;
            }
            else if (colors[y * level_image.width + x].r == 0) {
                level_array_data[y * level_image.width + x] = 0;
            }
        }      
    } 

    UnloadImage(level_image);
    //LoadSprite(space_tile, space_tile_texture,);
//-----------------------------------------------

//LOAD UI----------------------------------------------
    ui = new GameUILayer();
    ui->quit_pressed.Connect( [&](){this->OnQuitPressed();} );

    //ui->ConnectSignalTo(this);
    
    //LOAD PLAYER------------------------------------
    this_player = new PlayerShip( { (float)GetScreenWidth()/2 , (float)GetScreenHeight()/2} );
    entity_list[0] = this_player;
    this_player->camera = &camera;
    //TraceLog(LOG_INFO, "PLAYER CREATED");
    this_player->shoot.Connect( [&](){ui->OnPlayerShoot();} );
    ui->player = this_player;

//SETUP CAMERA--------------------------------------
    camera = { 0 };
    camera.target = (Vector2){ this_player->collision_rect.x, this_player->collision_rect.y};
    camera.offset = (Vector2){ this_player->position.x, this_player->position.y };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    
    AddToDrawList(entity_list, new Pickup( {500, 500} ));
    AddToDrawList(entity_list, new Pickup( {300, 600} ));
    AddToDrawList(entity_list, new Pickup( {500, 200} ));
    AddToDrawList(entity_list, new Pickup( {700, 300} ));
}


SCENE_ID GameScene::Update() {

    if(IsKeyPressed(KEY_TAB)) {
        settings.show_debug = !settings.show_debug;
    }
    DrawListUpdate(bullet_list);
    DrawListUpdate(entity_list);
    DrawListUpdate(effects_list);


    ui->Update();
    this_player->Update();

    camera.target = (Vector2){this_player->collision_rect.x, this_player->collision_rect.y};

    if( abs(this_player->velocity.x) > PLAYER_SPEED * 0.7f or abs(this_player->velocity.y) > PLAYER_SPEED * 0.7f) {
        camera.zoom = Lerp(camera.zoom, 0.8f, .005);
    }
    else {
        camera.zoom = Lerp(camera.zoom, 1.2f, .01);
    }
    //TraceLog(LOG_INFO, "PLAYER VELOCITY, (%f %f)", this_player->velocity.x, this_player->velocity.y);
    return return_scene;
}

void GameScene::Draw() {
    //TraceLog(LOG_INFO, "DRAW GAMESCEME");


    ClearBackground(BLACK);
    
    DrawTexturePro(bg_texture,  {0,0,(float)bg_texture.width,(float)bg_texture.height}, 
                                {0,0,(float)GetScreenWidth(),
                                (float)GetScreenHeight()},
                                {0},
                                0.0,
                                WHITE);

//------------------------BEGIN WORLDSPACE
    BeginMode2D(camera);

    DrawLevel();

    if(settings.show_debug) {
        DrawDebug();
    }
 
    DrawListDraw(bullet_list);
    DrawListDraw(entity_list);
    DrawListDraw(effects_list);
    
    EndMode2D();
//------------------------END WORLDSPACE

    ui->Draw();
}

GameScene::~GameScene() {

    
    delete[] level_array_data;
    //delete this_player;
    delete ui;
    UnloadTexture(space_tile_texture);
    UnloadTexture(asteroid_texture);
    UnloadTexture(bg_texture);

    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(bullet_list[i] != nullptr) {
            delete(bullet_list[i]);
            bullet_list[i] = nullptr;
        }
        if(bullet_list[i] != nullptr) {
            delete(entity_list[i]);
            entity_list[i] = nullptr;
        }
    }
    //free(pu);
}

void GameScene::DrawLevel() {
    for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
            DrawTexture(space_tile_texture, x*TILE_SIZE, y*TILE_SIZE, WHITE);

            if(level_array_data[y * LEVEL_SIZE + x] == 0) {
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

                if(level_array_data[(iy) * LEVEL_SIZE + (ix)] == 0) {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, PINK);
                }
                else {
                    DrawRectangle((float)ix * TILE_SIZE, (float)iy * TILE_SIZE, TILE_SIZE,TILE_SIZE, BLUE);
                }
            }
        }
    }
}

void GameScene::OnQuitPressed() {
    //TraceLog(LOG_INFO, "SCENE QUIT");
    return_scene = SPLASH_SCENE;

}