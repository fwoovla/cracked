#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

GameMenu::GameMenu(){

    player_won = false;

    screen_center = { settings.resolution.x/2, settings.resolution.y/2 };

    CreateButton(exit_button, {screen_center.x, screen_center.y}, {300, 50}, RED, "exit");
    
    CreateButton(continue_button, {screen_center.x, screen_center.y + 200 }, {300, 50}, GREEN, "retry");

    button_sound = LoadSound("assets/button.wav");

    CreatePanel(menu_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f), 5.0f) ;
}

GameMenu::~GameMenu() {
    UnloadSound(button_sound);
}

void GameMenu::Draw() {
    DrawPanel(menu_panel);
    DrawButton(exit_button);
    DrawButton(continue_button);
}


void GameMenu::Update()
{

    float dt = GetFrameTime();

    UpdatePanel(menu_panel);

    if(IsButtonHovered(exit_button, settings.game_scale)) {
        if(exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exit.EmitSignal();
        }
    }

    if(IsButtonHovered(continue_button, settings.game_scale)) {
        if(continue_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if(player_won){
                to_staging.EmitSignal();
            }
            else {
                reset.EmitSignal();
            }
            
            CreatePanel(menu_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f), 5.0f);
        }
    }

    if(player_won) {
        continue_button.text = "continue";
        //CreateButton(continue_button, {screen_center.x, screen_center.y + 200 }, {300, 50}, GREEN, "continue");
    }
}
