#include "../../core/uilayers.h"

GameUILayer::GameUILayer(){
    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED );
    quit_button.default_color = GRAY;
}

GameUILayer::~GameUILayer() {

}

void GameUILayer::Draw() {
    DrawButton(quit_button);

}


void GameUILayer::Update()
{
    if(IsButtonHovered(quit_button)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //TraceLog(LOG_INFO, "QUIT BUTTON PRESSED ");
            quit_pressed.EmitSignal();
        }
    }
}

void GameUILayer::OnPlayerShoot(){
    TraceLog(LOG_INFO, "PLAYER SHOOT");
}