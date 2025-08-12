#include "../../core/global_def.h"

#define GUN_POWER_SCALER 50.0f

GameUILayer::GameUILayer(){
    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED, "X");
    quit_button.default_color = DARKGRAY;

    gun_power_rect = {10, 100, 20, 0.0 * GUN_POWER_SCALER};
    gun_power_color = YELLOW;

    button_sound = LoadSound("assets/button.wav");

    float hit_efect_wait_time = 0.2f;
    hit_effect_timer = new Timer(hit_efect_wait_time, false, false);
    hit_effect_timer->timout.Connect([&](){this->OnHitEffectTimeout();});
    hit_effect_alpha_value = 100;  
    hit_effect_alpha_step = 100/hit_efect_wait_time;
    show_hit_effect = false;

    CreateLabel(points_tag_label, {100, 30}, 40, RAYWHITE, "POINTS:");
    CreateLabel(points_value_label, {300, 30}, 50, GOLD, "0");
    animating_points = false;

    CreateLabel(scrap_tag_label, {(float)GetScreenWidth() - 300, 30}, 40, RAYWHITE, "SCRAP:");
    CreateLabel(scrap_value_label, {(float)GetScreenWidth() - 100, 30}, 50, GOLD, "0");

    countdown_time = 5;
    CreateLabel(countdown_label, {(float)GetScreenWidth() /2, (float)GetScreenHeight() /2}, 200, RAYWHITE, TextFormat("%i", countdown_time));
    countdown_timer = new Timer(1.0f, true, false);
    countdown_timer->timout.Connect( [&](){OnCountdownTimerTimeout();} );
    countdown_fade = 1.0;

    beep = LoadSound("assets/beep.wav");
    long_beep = LoadSound("assets/longbeep.wav");

}

GameUILayer::~GameUILayer() {
    delete countdown_timer;
    delete hit_effect_timer;
    UnloadSound(button_sound);
    UnloadSound(beep);
    UnloadSound(long_beep);
}

void GameUILayer::Draw() {

    if(!countdown_timer->IsDone()) {
        DrawLabel(countdown_label);
    }
    
    DrawLabel(points_tag_label);
    DrawLabel(points_value_label);

    DrawLabel(scrap_tag_label);
    DrawLabel(scrap_value_label);

    DrawButton(quit_button);

    DrawRectangle(  gun_power_rect.x-2,
                    GetScreenHeight() -10.0f - player->data.GUN_MAX_POWER * GUN_POWER_SCALER,
                    gun_power_rect.width+4,
                    player->data.GUN_MAX_POWER * GUN_POWER_SCALER,
                    DARKGRAY);

    DrawRectangleRec(gun_power_rect, gun_power_color);
    DrawRectangleV( {gun_power_rect.x, (float)GetScreenHeight() - player->data.GUN_MAX_POWER * GUN_POWER_SCALER * (float)0.3},
                    {gun_power_rect.width, 5},
                    RED);
    
    Vector2 health_center = {(float)(GetScreenWidth() - 20 ) * 0.5f , 50};
    for(int i = 0; i < player->data.health; i++) {
        DrawRectangle(health_center.x-1 + (i * 25) , health_center.y-1, 22, 22, WHITE );
        DrawRectangle(health_center.x + (i * 25) , health_center.y, 20, 20, RED );
        DrawRectangle(health_center.x-1 - (i * 25) , health_center.y-1, 22, 22, WHITE );
        DrawRectangle(health_center.x - (i * 25) , health_center.y, 20, 20, RED );
    }

    if(show_hit_effect) {
        DrawRectangle( 0,0, GetScreenWidth(), GetScreenHeight(), {50, 0, 0, (unsigned char)hit_effect_alpha_value} );
    }
}


void GameUILayer::Update()
{
    if(!countdown_timer->IsDone()) {
        countdown_timer->Update();
        if(countdown_time > 0) {
            countdown_label.text = TextFormat("%i", countdown_time);
        }
        else {
            countdown_label.text = "GO!";
            countdown_label.default_color = GOLD;
        }
        countdown_fade -= GetFrameTime();
        countdown_label.default_color = Fade(countdown_label.default_color, countdown_fade );

    }

    if(player == nullptr) {
        return;
    }

    if(animating_points) {
        points_value_label.text_size += 5;
        if(points_value_label.text_size >= 60) {
            points_value_label.text_size = 50;
            animating_points = false;
        }
    }
    points_value_label.text = TextFormat("%i", player->data.points);

    if(animating_scrap){
        scrap_value_label.text_size += 5;
        if(scrap_value_label.text_size >= 60) {
            scrap_value_label.text_size = 50;
            animating_scrap = false;
        }
    }
    scrap_value_label.text = TextFormat("%i", player->data.scrap_amount);

    float dt = GetFrameTime();
    gun_power_rect.y = GetScreenHeight() -10.0f - player->data.gun_power * GUN_POWER_SCALER;
    gun_power_rect.height = player->data.gun_power * GUN_POWER_SCALER;
    if(player->data.gun_power < player->data.GUN_MAX_POWER * 0.3f) {
        gun_power_color = MAGENTA;
    }
    else {
        gun_power_color = YELLOW;
    }
    if(IsButtonHovered(quit_button)) {
        if(quit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            quit_pressed.EmitSignal();
        }
    }
    if(show_hit_effect) {
        hit_effect_timer->Update();
        hit_effect_alpha_value += (float)hit_effect_alpha_step * GetFrameTime();
    }
}

void GameUILayer::OnPlayerShoot(){
}

void GameUILayer::OnPlayerHit(){
    show_hit_effect = true;
    hit_effect_timer->Start();
}

void GameUILayer::OnPlayerPickedUpScrap(){
    animating_scrap = true;
    scrap_value_label.text_size = 10;
}

void GameUILayer::OnHitEffectTimeout(){
    show_hit_effect = false;
}

void GameUILayer::OnPlayerKilledEnemy(){
    animating_points = true;
    points_value_label.text_size = 10;
}

void GameUILayer::OnCountdownTimerTimeout(){
    countdown_time -=1;
    countdown_fade = 1.0;
    
    if(countdown_time < 1) {
        countdown_timer->Stop();
        PlaySound(long_beep);
    }
    else {
        PlaySound(beep);
    }
}