#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

ShipyardMenu::ShipyardMenu(){

    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    CreateButton(exit_button, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() /2}, {300, 50}, RED, "exit");
    
    CreateButton(continue_button, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() /2 + 200 }, {300, 50}, GREEN, "retry");

    button_sound = LoadSound("assets/button.wav");

    CreatePanel(menu_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f), 5.0f) ;
}

ShipyardMenu::~ShipyardMenu() {
    UnloadSound(button_sound);
}

void GameMenu::Draw() {
    DrawPanel(menu_panel);
    DrawButton(exit_button);
    DrawButton(continue_button);
}


void ShipyardMenu::Update()
{

    float dt = GetFrameTime();

    UpdatePanel(menu_panel);

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
            
            CreatePanel(menu_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f), 5.0f);
        }
    }
}
