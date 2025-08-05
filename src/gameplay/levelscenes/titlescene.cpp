#include "../../core/global_def.h"


TitleScene::TitleScene() {
    scene_id = TITLE_SCENE;
    return_scene = NO_SCENE;
    //game_settings = _game_settings;


    bg_texture = LoadTexture("assets/levelbg1.png");

    Vector2 screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 - GetScreenHeight() / 3 };

    LoadSpriteCentered(logo, LoadTexture("assets/logo_pic_large.png"), screen_center);
    //ScaleSprite(logo, {2,2});


    ui = new TitleUiLayer();
    ui->play_pressed.Connect( [&](){this->OnPlayPressed();} );
    ui->quit_pressed.Connect( [&](){this->OnQuitPressed();} );

    double wait_time = 1.0;
    fade_timer = new Timer(wait_time, false, false);
    //timer->ConnectSignalTo(this);
    fade_timer->timout.Connect([&](){this->OnFadeOut();});
    alpha_value = 0;  
    alpha_step = 255/wait_time;
    transitioning = false;
}


SCENE_ID TitleScene::Update() {
    ui->Update();

    if(transitioning) {
        fade_timer->Update();
        alpha_value += (float)alpha_step * GetFrameTime();
    }

    if(IsKeyPressed(KEY_ENTER)) {
        return_scene = GAME_SCENE;
    }
    return return_scene;
}

void TitleScene::Draw() {
    ClearBackground(BLUE);
    DrawTexturePro(bg_texture,  {0,0,(float)bg_texture.width,(float)bg_texture.height}, 
                                {0,0,(float)GetScreenWidth(),
                                (float)GetScreenHeight()},
                                {0},
                                0.0,
                                WHITE);
    DrawSprite(logo);
    ui->Draw();

    if(transitioning) {
        DrawRectangle( 0,0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, (unsigned char)alpha_value} );
    }
}

TitleScene::~TitleScene() {
    //TraceLog(LOG_INFO, "DESTROY TITLE");
    UnloadTexture(logo.texture);
    UnloadTexture(bg_texture);
    delete ui;
}

void TitleScene::OnPlayPressed() {
    //TraceLog(LOG_INFO, "SCENE PLAY");
    transitioning = true;
    fade_timer->Start();
    //return_scene = GAME_SCENE;

}

void TitleScene::OnQuitPressed() {
    //TraceLog(LOG_INFO, "SCENE QUIT");
    game_running = false;
    return_scene = SPLASH_SCENE;

}
void TitleScene::OnFadeOut() {
    //TraceLog(LOG_INFO, "SCENE QUIT");
    return_scene = GAME_SCENE;

}