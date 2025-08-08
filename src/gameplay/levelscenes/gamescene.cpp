
#include "../../core/global_def.h"
#include <raymath.h>
//#include "scenes.h"
//#include "scenes.h"

#define MAX_ENEMIES 4

int* level_array_data;

BaseEntity *bullet_list[DRAW_LIST_SIZE] = {nullptr};
BaseEntity *entity_list[DRAW_LIST_SIZE] = {nullptr};
BaseEntity *effects_list[DRAW_LIST_SIZE] = {nullptr};
std::vector<BaseEntity*> *collision_data[LEVEL_SIZE * LEVEL_SIZE] = {nullptr};


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
            if(colors[y * level_image.width + x].r == 0 and colors[y * level_image.width + x].g == 0 and colors[y * level_image.width + x].b == 0) {
                level_array_data[y * level_image.width + x] = 1;
            }
            else if (colors[y * level_image.width + x].r == 255 and colors[y * level_image.width + x].g == 255 and colors[y * level_image.width + x].b == 255) {
                level_array_data[y * level_image.width + x] = 0;
            }
            else if (colors[y * level_image.width + x].g == 255) {
                pickup_positions.push_back((Vector2){(float)x * TILE_SIZE,(float)y * TILE_SIZE});
                TraceLog(LOG_INFO, "PICKUP ADDED,                         %i %i",x*TILE_SIZE, y*TILE_SIZE);
            }
            else if (colors[y * level_image.width + x].r == 255) {
                enemy_positions.push_back((Vector2){(float)x * TILE_SIZE,(float)y * TILE_SIZE});
                TraceLog(LOG_INFO, "ENEMY ADDED,                         %i %i",x*TILE_SIZE, y*TILE_SIZE);
            }
        }      
    } 

    UnloadImage(level_image);
    //LoadSprite(space_tile, space_tile_texture,);
//-----------------------------------------------

    enemy_spawn_timer = new Timer(1.0, true, false);
    enemy_spawn_timer->timout.Connect( [&](){this->OnEnemySpawnTimerTimeout();} );
    spawned_eney_amount = 0;

//LOAD UI----------------------------------------------
    ui = new GameUILayer();
    ui->quit_pressed.Connect( [&](){this->OnQuitPressed();} );

    menu = new GameMenu();
    menu->exit.Connect( [&](){this->OnMenuExit();} );
    menu->reset.Connect( [&](){this->OnMenuRestart();} );
    show_menu = false;
    
    //LOAD PLAYER------------------------------------
    this_player = new PlayerShip( { (float)GetScreenWidth()/2 , (float)GetScreenHeight()/2} );
    entity_list[0] = this_player;
    this_player->camera = &camera;
    //TraceLog(LOG_INFO, "PLAYER CREATED");
    this_player->shoot.Connect( [&](){ui->OnPlayerShoot();} );
    this_player->player_hit.Connect( [&](){ui->OnPlayerHit();} );
    this_player->dead.Connect( [&](){OnPlayerDead();} );
    ui->player = this_player;

//SETUP CAMERA--------------------------------------
    camera = { 0 };
    camera.target = (Vector2){ this_player->collision_rect.x, this_player->collision_rect.y};
    camera.offset = (Vector2){ this_player->position.x, this_player->position.y };
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;

    Pickup *np = new Pickup( pickup_positions[GetRandomValue(0, pickup_positions.size() - 1)] );
    AddToDrawList(entity_list, np);
    np->pickedup.Connect( [&](){OnPickUpPickedUp();} );

    enemy_explosion_sound = LoadSound("assets/explode1.wav");
    game_over_sound = LoadSound("assets/gameover.wav");
    pickup_sound = LoadSound("assets/pickup.wav");
    bg_music = LoadMusicStream("assets/levelmusic1.wav");
    SetMusicVolume(bg_music, 0.5f);
    PlayMusicStream(bg_music);

}


SCENE_ID GameScene::Update() {

    UpdateMusicStream(bg_music);

    if(IsKeyPressed(KEY_TAB)) {
        settings.show_debug = !settings.show_debug;
    }
    DrawListUpdate(bullet_list);
    DrawListUpdate(entity_list);
    DrawListUpdate(effects_list);

    enemy_spawn_timer->Update();
    ui->Update();

    camera.target = (Vector2){this_player->collision_rect.x, this_player->collision_rect.y};

    if( abs(this_player->velocity.x) > PLAYER_SPEED * 0.7f or abs(this_player->velocity.y) > PLAYER_SPEED * 0.7f) {
        camera.zoom = Lerp(camera.zoom, 1.0f, .005);
    }
    else {
        camera.zoom = Lerp(camera.zoom, 2.2f, .01);
    }
    if(show_menu) {
        menu->Update();
    }

    return return_scene;
}

void GameScene::Draw() {
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
    //this_player->Draw();
    DrawListDraw(effects_list);
    
    EndMode2D();
//------------------------END WORLDSPACE

    ui->Draw();

    if(show_menu) {
        menu->Draw();
    }
}

GameScene::~GameScene() {

    
    delete[] level_array_data;
    //delete this_player;
    delete ui;
    delete menu;
    UnloadSound(enemy_explosion_sound);
    UnloadSound(game_over_sound);
    UnloadSound(pickup_sound);
    UnloadMusicStream(bg_music);

    UnloadTexture(space_tile_texture);
    UnloadTexture(asteroid_texture);
    UnloadTexture(bg_texture);
    delete enemy_spawn_timer;

    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(bullet_list[i] != nullptr) {
            delete(bullet_list[i]);
            bullet_list[i] = nullptr;
        }
        if(entity_list[i] != nullptr) {
            delete(entity_list[i]);
            entity_list[i] = nullptr;
        }
        if(effects_list[i] != nullptr) {
            delete(effects_list[i]);
            effects_list[i] = nullptr;
        }
    }
}

void GameScene::DrawLevel() {
    for(int x = 0; x < LEVEL_SIZE; x++) {
        for(int y = 0; y < LEVEL_SIZE; y++) {
            DrawTexture(space_tile_texture, x*TILE_SIZE, y*TILE_SIZE, WHITE);

            if(level_array_data[y * LEVEL_SIZE + x] == 1) {
                DrawTexture(asteroid_texture, x*TILE_SIZE, y*TILE_SIZE, WHITE);
            }
        }
    }
}

void GameScene::DrawDebug() {
    if(settings.show_debug){
        
    }
}

void GameScene::OnQuitPressed() {
    //TraceLog(LOG_INFO, "SCENE QUIT");
    return_scene = SPLASH_SCENE;
}

void GameScene::OnPickUpPickedUp() {
    PlaySound(pickup_sound);
    Pickup *np = new Pickup( pickup_positions[GetRandomValue(0, pickup_positions.size() - 1)] );
    AddToDrawList(entity_list, np);
    np->pickedup.Connect( [&](){OnPickUpPickedUp();} );
    TraceLog(LOG_INFO, "NEW PICKUP");
}
void GameScene::OnEnemySpawnTimerTimeout(){
    if(spawned_eney_amount >= MAX_ENEMIES) {
        return;
    }
    //return;
    spawned_eney_amount++;

    EnemyShip *np = new EnemyShip( enemy_positions[GetRandomValue(0, enemy_positions.size() - 1)] );
    AddToDrawList(entity_list, np);
    np->dead.Connect( [&](){OnEnemyDead();} );
    np->player_killed_enemy.Connect( [&](){OnPlayerKilledEnemy();} );
    np->player_killed_enemy.Connect( [&](){ui->OnPlayerKilledEnemy();} );
    np->target = this_player;
    TraceLog(LOG_INFO, "NEW ENEMY, %i  (%f %f)", spawned_eney_amount, np->position.x, np->position.y);
}

void GameScene::OnEnemyDead(){
    PlaySound(enemy_explosion_sound);
    spawned_eney_amount--;
}

void GameScene::OnPlayerKilledEnemy(){
    TraceLog(LOG_INFO, "NEW POINTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!NEW POINTS");
    this_player->points += 100;
}

void GameScene::OnPlayerDead(){
    TraceLog(LOG_INFO, "                               -------------------------------------------------PLAYER DEAD");
    PlaySound(game_over_sound);
    for(int i = 0; i < DRAW_LIST_SIZE; i++) {
        if(bullet_list[i] != nullptr) {
            delete(bullet_list[i]);
            bullet_list[i] = nullptr;
        }
        if(entity_list[i] != nullptr) {
            if(entity_list[i]->id != 1){
                delete(entity_list[i]);
                entity_list[i] = nullptr;
            }
        }

        if(effects_list[i] != nullptr) {
            delete(effects_list[i]);
            effects_list[i] = nullptr;
        }
    }
    AddToDrawList(effects_list, new ExplosionEffect(this_player->position));

    //this_player = nullptr;
    enemy_spawn_timer->Stop();

    show_menu = true;
}

void GameScene::OnMenuExit(){
    return_scene = SPLASH_SCENE;
}

void GameScene::OnMenuRestart(){
    spawned_eney_amount = 0;
    enemy_spawn_timer->Start();
    this_player->Reset();
    show_menu = false;
    Pickup *np = new Pickup( pickup_positions[GetRandomValue(0, pickup_positions.size() - 1)] );
    AddToDrawList(entity_list, np);
    np->pickedup.Connect( [&](){OnPickUpPickedUp();} );
}