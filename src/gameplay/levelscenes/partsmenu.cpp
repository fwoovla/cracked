#include "../../core/global_def.h"


PartsMenu::PartsMenu(){

    screen_center = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2 };
    float margin = 100.0f;
    CreateLabel(header, {screen_center.x, 50 + margin}, 50, GOLD, "Parts Shop");
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

    CreateLabel(equipped_part_label, {margin + 100, margin + 200}, 30, RAYWHITE, "");
    //equipped_part_label_text = "";
    //equipped_part_label_position = {margin + 100, margin + 200};
    CreateLabelList(equipped_part_stat_list, {margin + 100, margin + 300}, 200, 20, 50, YELLOW, RAYWHITE, "...");
    AddLabelToList(equipped_part_stat_list, "stat: fun");

    selected_location = NONE;
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
    DrawLabelCentered(header);

    DrawLabel(equipped_part_label);
    DrawLabelList(equipped_part_stat_list);

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
        if(selected_location != THRUSTERS) {
            selected_location = THRUSTERS;
            engine_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "THRUSTERS";
            equipped_part_stat_list.header_text = player_data.thrusters_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("top speed %.f", player_data.thrusters_part.THRUSTER_SPEED) );
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.f", player_data.thrusters_part.weight) );
        }
    }
    else if(CheckCollisionPointRec(GetMousePosition(), gun_area)) {
        if(selected_location != MAIN_GUN) {
            selected_location = MAIN_GUN;
            gun_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "MAIN GUN";
            equipped_part_stat_list.header_text = player_data.main_gun_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.f", player_data.main_gun_part.GUN_DELAY) );
            AddLabelToList(equipped_part_stat_list, TextFormat("power %.2f", player_data.main_gun_part.GUN_POWER_USE) );
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.f", player_data.main_gun_part.weight) );
        }
    }
    else {
        selected_location = NONE;
        equipped_part_stat_list.header_text = "";
        ClearLabelList(equipped_part_stat_list);
        equipped_part_label.text = "";
        gun_outline_sprite.modulate = GRAY;
        engine_outline_sprite.modulate = GRAY;
    }
}
