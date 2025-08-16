#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

ShipyardMenu::ShipyardMenu(){

    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };
    float margin = 100.0f;
    CreateLabel(header, {screen_center.x, 50 + margin}, 50, RAYWHITE, "Shipyard");
    CreatePanel(menu_panel, {margin, margin}, {(float)GetScreenWidth() - (margin*2), (float)GetScreenHeight() - (margin*2)}, BLACK, 1.0f) ;;
    CreateButton(exit_button, { screen_center.x, screen_center.y + 400}, {300, 50}, RED, "back");
    button_sound = LoadSound("assets/button.wav");
}

ShipyardMenu::~ShipyardMenu() {
    UnloadSound(button_sound);
}

void ShipyardMenu::Draw() {
    DrawPanel(menu_panel);
    DrawButton(exit_button);
    DrawLabel(header);
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
            shipyard_close.EmitSignal();
            ResetPanel(menu_panel);
        }
    }
}
