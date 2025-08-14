#include "../../core/global_def.h"


StagingUILayer::StagingUILayer() {
    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    CreateButton(start_button, screen_center, {200, 100}, GREEN, "play");
    start_button.default_color = DARKGREEN;
    start_button.text_size = 50;

    CreateButton(settings_button, {screen_center.x, screen_center.y + 150}, {200, 100}, YELLOW, "settings");
    settings_button.default_color = GOLD;

    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED, "X");
    quit_button.default_color = DARKGRAY;

    button_sound = LoadSound("assets/button.wav");
    
    CreatePanel(menu_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f), 5.0f) ;
    
}

StagingUILayer::~StagingUILayer() {
    UnloadSound(button_sound);
}

void StagingUILayer::Draw() {
    DrawPanel(menu_panel);

    DrawButton(start_button);
    DrawButton(settings_button);
    DrawButton(quit_button);
}

void StagingUILayer::Update() {

    UpdatePanel(menu_panel);
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
