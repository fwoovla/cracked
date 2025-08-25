#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

ShipyardMenu::ShipyardMenu(){

    screen_center = { settings.resolution.x/2, settings.resolution.y/2 };
    float margin = 100.0f;
    CreateLabel(header, {screen_center.x, margin}, 40, GOLD, "Shipyard");
    CreatePanel(menu_panel, {margin, margin}, {settings.resolution.x - (margin*2), settings.resolution.y - (margin*2)}, BLACK, 1.0f) ;;
    CreateButton(exit_button, { screen_center.x, menu_panel.size.y + margin}, {300, 50}, ORANGE, "back");
    button_sound = LoadSound("assets/button.wav");
}

ShipyardMenu::~ShipyardMenu() {
    UnloadSound(button_sound);
}

void ShipyardMenu::Draw() {
    DrawPanel(menu_panel);
    DrawButton(exit_button);
    DrawLabelCentered(header);
}


void ShipyardMenu::Update()
{

    float dt = GetFrameTime();

    UpdatePanel(menu_panel);

    if(IsButtonHovered(exit_button, settings.game_scale)) {
        if(exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            shipyard_close.EmitSignal();
            ResetPanel(menu_panel);
        }
    }
}
