#include "../../core/scenes.h"

SplashScreen::SplashScreen() {

    double wait_time = 1.0;

    scene_id = SPLASH_SCENE;
    return_scene = NO_SCENE;
    timer = new Timer(wait_time, true, true);
    timer->ConnectSignalTo(this);
    alpha_value = 0;  
    alpha_step = 255/wait_time;

    Vector2 screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };
    LoadSpriteCentered(logo, LoadTexture("assets/logo_pic_large.png"), screen_center);
    ScaleSprite(logo, {2.0,2.0});
}


SCENE_ID SplashScreen::Update() {
    timer->Update();
    alpha_value += (float)alpha_step * GetFrameTime();

    return return_scene;
}

void SplashScreen::Draw() {
    ClearBackground(RAYWHITE);
    DrawSprite(logo);
    DrawRectangle( 0,0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, (unsigned char)alpha_value} );
    //DrawText("SPLASH SCENE", 200, 200, 40, BLACK);
}

SplashScreen::~SplashScreen() {
    UnloadTexture(logo.texture);
    delete timer;
}

void SplashScreen::OnSignal(SIGNAL signal) {
    return_scene = TITLE_SCENE;
}