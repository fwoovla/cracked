#include "../../core/uilayers.h"

TitleUiLayer::TitleUiLayer() {
    Vector2 screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    CreateButton(start_button, screen_center, {200, 100}, GREEN );
    start_button.default_color = DARKGREEN;

    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED );
    quit_button.default_color = GRAY;
    
}

void TitleUiLayer::Draw() {
    DrawButton(start_button);
    DrawButton(quit_button);
}

void TitleUiLayer::Update() {

    if(IsButtonHovered(quit_button)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "QUIT BUTTON PRESSED ");
            EmitSignal(END_GAME);
        }
    }
    //TraceLog(LOG_INFO, "UI UPDATE");
    if(IsButtonHovered(start_button)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "BUTTON PRESSED ");
            EmitSignal(PLAY_PRESSED);
        }        
    }
}

void TitleUiLayer::Destroy() {

}
