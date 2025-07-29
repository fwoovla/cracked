#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

GameUILayer::GameUILayer(){
    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED );
    quit_button.default_color = GRAY;

    gun_power_rect = {10, 100, 20, GUN_MAX_POWER * GUN_POWER_SCALER};
    gun_power_color = YELLOW;
}

GameUILayer::~GameUILayer() {

}

void GameUILayer::Draw() {
    DrawButton(quit_button);
    DrawRectangleRec(gun_power_rect, gun_power_color);

}


void GameUILayer::Update()
{
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
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            quit_pressed.EmitSignal();
        }
    }
}

void GameUILayer::OnPlayerShoot(){
    TraceLog(LOG_INFO, "PLAYER SHOOT");
}