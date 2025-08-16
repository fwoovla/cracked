#include "../../core/global_def.h"


StagingScene::StagingScene() {
    scene_id = STAGING_SCENE;
    return_scene = NO_SCENE;

    bg_texture = LoadTexture("assets/staging_bg.png");

    Vector2 screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 - GetScreenHeight() / 3 };

    //LoadSpriteCentered(logo, LoadTexture("assets/logo_pic_large.png"), screen_center);

    ui = new StagingUILayer();
    ui->quit_pressed.Connect( [&](){OnQuitPressed();} );
    ui->parts_pressed.Connect( [&](){OnPartsPressed();} );
    ui->shipyard_pressed.Connect( [&](){OnShipyardPressed();} );
    ui->battle_pressed.Connect( [&](){OnBattlePressed();} );

    double wait_time = 0.5;
    fade_timer = new Timer(wait_time, false, false);
    fade_timer->timout.Connect([&](){OnFadeOut();});
    alpha_value = 0;
    alpha_step = 255/wait_time;
    transitioning = false;

    LoadSpriteCentered(door_light, LoadTexture("assets/doorlight.png"), {50, 350}, 2, 30.0f, 0.5f);
    ScaleSprite(door_light, {2,2});

    shop_area = {10, 400, 450, 450};
    battle_area = {1100, 100, 750, 500};

    bg_music = LoadMusicStream("assets/intromusic.wav");
    SetMusicVolume(bg_music, 0.5f);
    PlayMusicStream(bg_music);
}


SCENE_ID StagingScene::Update() {
    UpdateMusicStream(bg_music);

    ui->Update();
    AnimateSprite(door_light);

    if(transitioning) {
        fade_timer->Update();
        alpha_value += (float)alpha_step * GetFrameTime();
    }

    if(!ui->menus_are_open) {

        if(CheckCollisionPointRec(GetMousePosition(), shop_area)) {
            ui->ShowShopPanel();
        }
        else {
            ui->HideShopPanel();
        }
        if(CheckCollisionPointRec(GetMousePosition(), battle_area)) {
            ui->ShowBattlePanel();
        }
        else {
            ui->HideBattlePanel();
        }

    }
    if(IsKeyPressed(KEY_ENTER)) {
        return_scene = GAME_SCENE;
    }
    return return_scene;
}

void StagingScene::Draw() {
    ClearBackground(GetColor(0x251f0f));
    DrawTexturePro(bg_texture,  {0,0,(float)bg_texture.width,(float)bg_texture.height}, 
                                {0,0,(float)GetScreenWidth(),
                                (float)GetScreenHeight()},
                                {0},
                                0.0,
                                WHITE);
    //DrawSprite(logo);
    DrawSprite(door_light);
   // DrawRectangleRec(shop_area, YELLOW);
    //DrawRectangleRec(battle_area, RED);
    ui->Draw();



    if(transitioning) {
        DrawRectangle( 0,0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, (unsigned char)alpha_value} );
    }
}

StagingScene::~StagingScene() {
    //UnloadTexture(logo.texture);
    UnloadTexture(bg_texture);
    UnloadTexture(door_light.texture);
    UnloadMusicStream(bg_music);
    delete ui;
}

void StagingScene::OnQuitPressed() {
    game_running = false;

}
void StagingScene::OnFadeOut() {
    return_scene = GAME_SCENE;
}

void StagingScene::OnPartsPressed() {
    TraceLog(LOG_INFO, "PARTS PRESSED");
}

void StagingScene::OnShipyardPressed() {
}

void StagingScene::OnBattlePressed() {
    transitioning = true;
    fade_timer->Start();
}

