#include "../../core/global_def.h"


StagingUILayer::StagingUILayer() {
    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED, "X");
    quit_button.default_color = DARKGRAY;

    button_sound = LoadSound("assets/button.wav");
    
    CreatePanel(shop_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f));
    CreatePanel(battle_panel, {screen_center.x - 300, screen_center.y - 100}, {600, 400}, Fade(WHITE, 0.0f));
    
}

StagingUILayer::~StagingUILayer() {
    UnloadSound(button_sound);
}

void StagingUILayer::Draw() {
    DrawPanel(shop_panel);
    DrawPanel(battle_panel);

    DrawButton(quit_button);
}

void StagingUILayer::Update() {


    if(IsButtonHovered(quit_button)) {
        if(quit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            //TraceLog(LOG_INFO, "QUIT BUTTON PRESSED ");
            quit_pressed.EmitSignal();
        }
    }

}
