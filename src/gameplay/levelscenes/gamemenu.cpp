#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

GameMenu::GameMenu(){
    CreateButton(exit_button, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() /2}, {300, 50}, RED, "exit");
    
    CreateButton(continue_button, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() /2 + 200 }, {300, 50}, GREEN, "retry");

    button_sound = LoadSound("assets/button.wav");
}

GameMenu::~GameMenu() {
    UnloadSound(button_sound);
}

void GameMenu::Draw() {
    DrawButton(exit_button);
    DrawButton(continue_button);
}


void GameMenu::Update()
{

    float dt = GetFrameTime();
    if(IsButtonHovered(exit_button)) {
        if(exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exit.EmitSignal();
        }
    }

    if(IsButtonHovered(continue_button)) {
        if(continue_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            reset.EmitSignal();
        }
    }
}
