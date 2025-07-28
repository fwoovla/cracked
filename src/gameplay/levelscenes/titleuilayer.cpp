#include "../../core/global_def.h"

//#include "../../core/uilayers.h"

TitleUiLayer::TitleUiLayer() {
    Vector2 screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };

    CreateButton(start_button, screen_center, {200, 100}, GREEN );
    start_button.default_color = DARKGREEN;

    CreateButton(quit_button, { (float)GetScreenWidth() - 40, 20 }, {30, 30}, RED );
    quit_button.default_color = GRAY;
    
}

TitleUiLayer::~TitleUiLayer() {

}

void TitleUiLayer::Draw() {
    DrawButton(start_button);
    DrawButton(quit_button);
}

void TitleUiLayer::Update() {

    if(IsButtonHovered(quit_button)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "QUIT BUTTON PRESSED ");
            quit_pressed.EmitSignal();
        }
    }
    //TraceLog(LOG_INFO, "UI UPDATE");
    if(IsButtonHovered(start_button)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            TraceLog(LOG_INFO, "PLAY BUTTON PRESSED ");
            play_pressed.EmitSignal();
        }        
    }
}
