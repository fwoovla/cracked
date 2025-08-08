#include "../../core/global_def.h"

//#include "../../core/uilayers.h"

TitleUiLayer::TitleUiLayer() {
    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    CreateButton(start_button, screen_center, {200, 100}, GREEN, "play");
    start_button.default_color = DARKGREEN;
    start_button.text_size = 50;

    CreateButton(settings_button, {screen_center.x, screen_center.y + 150}, {200, 100}, YELLOW, "settings");
    settings_button.default_color = GOLD;

    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED, "X");
    quit_button.default_color = DARKGRAY;

    button_sound = LoadSound("assets/button.wav");
    
}

TitleUiLayer::~TitleUiLayer() {
    UnloadSound(button_sound);
}

void TitleUiLayer::Draw() {
    DrawRectangleV( {screen_center.x - 200, screen_center.y - 100}, {400, 400}, DARKGRAY);
    DrawButton(start_button);
    DrawButton(settings_button);
    DrawButton(quit_button);
}

void TitleUiLayer::Update() {

    if(IsButtonHovered(quit_button)) {
        if(quit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //TraceLog(LOG_INFO, "QUIT BUTTON PRESSED ");
            quit_pressed.EmitSignal();
        }
    }
    //TraceLog(LOG_INFO, "UI UPDATE");
    if(IsButtonHovered(start_button)) {
        if(start_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //TraceLog(LOG_INFO, "PLAY BUTTON PRESSED ");
            play_pressed.EmitSignal();
        }        
    }
    if(IsButtonHovered(settings_button)) {
        if(settings_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        }        
    }
}
