#include "../../core/global_def.h"

#define GUN_POWER_SCALER 20.0f

PartsMenu::PartsMenu(){

    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };
    float margin = 100.0f;
    CreateLabel(header, {screen_center.x, 50 + margin}, 50, RAYWHITE, "Parts Shop");
    CreatePanel(menu_panel, {margin, margin}, {(float)GetScreenWidth() - (margin*2), (float)GetScreenHeight() - (margin*2)}, BLACK, 1.0f) ;;
    CreateButton(exit_button, { screen_center.x, screen_center.y + 400}, {300, 50}, RED, "back");
    button_sound = LoadSound("assets/button.wav");

    LoadSpriteCentered(ship_outline_sprite, LoadTexture("assets/shipoutline.png"), screen_center);
    ScaleSprite(ship_outline_sprite, {3,3});

    LoadSpriteCentered(gun_outline_sprite, LoadTexture("assets/gunoutline.png"), {screen_center.x+150, screen_center.y});
    ScaleSprite(gun_outline_sprite, {3,3});
    gun_area = gun_outline_sprite.dest;
    gun_area.x -= (gun_area.width * 0.5f);
    gun_area.y -= (gun_area.height * 0.5f);

    LoadSpriteCentered(engine_outline_sprite, LoadTexture("assets/engineoutline.png"), {screen_center.x-200, screen_center.y});
    ScaleSprite(engine_outline_sprite, {3,3});
    engine_area = engine_outline_sprite.dest;
    engine_area.x -= (engine_area.width * 0.5f);
    engine_area.y -= (engine_area.height * 0.5f);

    CreateLabel(equipped_part_label, {margin + 50, margin + 50}, 40, RAYWHITE, "...");
}

PartsMenu::~PartsMenu() {
    UnloadSound(button_sound);
    UnloadTexture(ship_outline_sprite.texture);
    UnloadTexture(gun_outline_sprite.texture);
    UnloadTexture(engine_outline_sprite.texture);
}

void PartsMenu::Draw() {
    DrawPanel(menu_panel);

    DrawSprite(ship_outline_sprite);
    DrawSprite(engine_outline_sprite);
    DrawSprite(gun_outline_sprite);

    DrawButton(exit_button);
    DrawLabel(header);

    DrawLabel(equipped_part_label);

    //DrawRectangleRec(gun_area,RED);
    //DrawRectangleRec(engine_area,RED);
}


void PartsMenu::Update()
{

    float dt = GetFrameTime();

    UpdatePanel(menu_panel);

    if(IsButtonHovered(exit_button)) {
        if(exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            parts_close.EmitSignal();
            ResetPanel(menu_panel);
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), engine_area)) {
        engine_outline_sprite.modulate = ORANGE;
    }
    else {
        engine_outline_sprite.modulate = GRAY;
    }

    if(CheckCollisionPointRec(GetMousePosition(), gun_area)) {
        gun_outline_sprite.modulate = ORANGE;
    }
    else {
        gun_outline_sprite.modulate = GRAY;
    }
}
