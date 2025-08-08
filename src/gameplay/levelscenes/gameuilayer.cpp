#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

GameUILayer::GameUILayer(){
    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED, "X");
    quit_button.default_color = DARKGRAY;

    gun_power_rect = {10, 100, 20, GUN_MAX_POWER * GUN_POWER_SCALER};
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

}

GameUILayer::~GameUILayer() {
    UnloadSound(button_sound);
}

void GameUILayer::Draw() {
    
    DrawLabel(points_tag_label);
    DrawLabel(points_value_label);

    DrawButton(quit_button);

    DrawRectangle(gun_power_rect.x-2, gun_power_rect.y-2, gun_power_rect.width+4, gun_power_rect.y, WHITE);
    DrawRectangleRec(gun_power_rect, gun_power_color);

    Vector2 health_center = {(float)(GetScreenWidth() - 20 ) * 0.5f , 50};
    for(int i = 0; i < player->health; i++) {
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

    points_value_label.text = TextFormat("%i", player->points);

    float dt = GetFrameTime();
    gun_power_rect.y = GetScreenHeight() -10.0f - player->gun_power * GUN_POWER_SCALER;
    gun_power_rect.height = player->gun_power * GUN_POWER_SCALER;
    if(player->gun_power < GUN_MAX_POWER * 0.3f) {
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
    //TraceLog(LOG_INFO, "PLAYER SHOOT");
}

void GameUILayer::OnPlayerHit(){
    //TraceLog(LOG_INFO, "PLAYER HIT");
    show_hit_effect = true;
    hit_effect_timer->Start();
}

void GameUILayer::OnHitEffectTimeout(){
    show_hit_effect = false;
}

void GameUILayer::OnPlayerKilledEnemy(){
    TraceLog(LOG_INFO, "STRTING ANIMATION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    animating_points = true;
    points_value_label.text_size = 10;
}