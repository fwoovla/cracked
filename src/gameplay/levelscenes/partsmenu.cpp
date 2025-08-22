#include "../../core/global_def.h"

#define PURCHASE_HEIGHT 175.0f

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
    
    CreateButton(part_exit_button, {margin + 460, margin + 200}, {80, 80}, RED, "X");

    CreateLabel(equipped_part_header, {margin + 100, margin + 150}, 40, GRAY, "Equipped Part");
    CreateLabel(equipped_part_label, {margin + 100, margin + 200}, 30, RAYWHITE, "");
    CreateLabelList(equipped_part_stat_list, {margin + 100, margin + 300}, 200, 20, 50, YELLOW, RAYWHITE, "");

    selected_location = NONE;
    hovered_location = NONE;

    ppasp = {(float)GetScreenWidth() - 600.0f, margin + 150};
    hovered_purchase_part_index = -1;
    selected_purchase_part_index = -1;
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

    DrawLabel(equipped_part_header);
    DrawLabel(equipped_part_label);
    DrawLabelList(equipped_part_stat_list);

    if(selected_location != NONE) {
        DrawButton(part_exit_button);

        for(int i = 0; i < purchase_part_areas.size(); i++) {
            DrawRectangleLines(purchase_part_areas[i].x, purchase_part_areas[i].y, purchase_part_areas[i].width, purchase_part_areas[i].height, WHITE);
            if(selected_location == MAIN_GUN) {
                DrawMainGunPurchaseStats(i);
            }
            if(selected_location == THRUSTERS) {
                DrawThrusterPurchaseStats(i);
            }
            if(hovered_purchase_part_index == i) {
                DrawRectangleRec( purchase_part_areas[i], Fade(GRAY, 0.2) );
            }
        }
    }
}


void PartsMenu::Update()
{

    float dt = GetFrameTime();
    UpdatePanel(menu_panel);

    if(IsButtonHovered(exit_button, settings.game_scale)) {
        if(exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            parts_close.EmitSignal();
            ResetPanel(menu_panel);
        }
    }

    if(IsButtonHovered(part_exit_button, settings.game_scale)) {
        if(part_exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selected_location = NONE;
            hovered_location = NONE;
            equipped_part_stat_list.header_text = "";
            ClearLabelList(equipped_part_stat_list);
            equipped_part_label.text = "";
            gun_outline_sprite.modulate = GRAY;
            engine_outline_sprite.modulate = GRAY;
            purchase_part_areas.clear();
            hovered_purchase_part_index = -1;
            selected_purchase_part_index = -1;

        }
    }
    
    if(selected_location != NONE) {
        hovered_purchase_part_index = -1;
        for(int i = 0; i < purchase_part_areas.size(); i++) {
            if(CheckCollisionPointRec(GetMousePosition(), purchase_part_areas[i])) {
                hovered_purchase_part_index =i;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    TraceLog(LOG_INFO, "part clicked %i", i);
                    selected_purchase_part_index = i;
                }
            }
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), engine_area)) {
        if(hovered_location != THRUSTERS and selected_location == NONE) {
            hovered_location = THRUSTERS;
            engine_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "THRUSTERS";
            equipped_part_stat_list.header_text = player_data.thrusters_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("top speed %.2f", player_data.thrusters_part.THRUSTER_SPEED) );
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.thrusters_part.weight) );
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and selected_location == NONE) {
            selected_location = THRUSTERS;
            for(int i = 0; i < thrusters_data.size(); i++) {
                Rectangle new_rect = {ppasp.x, (ppasp.y + (i*PURCHASE_HEIGHT)), 400, PURCHASE_HEIGHT};
                purchase_part_areas.push_back(new_rect);
            }
        }
    }
    else if(CheckCollisionPointRec(GetMousePosition(), gun_area)) {
        if(hovered_location != MAIN_GUN and selected_location == NONE) {
            hovered_location = MAIN_GUN;
            gun_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "MAIN GUN";
            equipped_part_stat_list.header_text = player_data.main_gun_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.main_gun_part.weight) );
            AddLabelToList(equipped_part_stat_list, TextFormat("power %.2f", player_data.main_gun_part.GUN_POWER_USE) );
            AddLabelToList(equipped_part_stat_list, TextFormat("shot delay %.2f", player_data.main_gun_part.GUN_DELAY) );
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and selected_location == NONE) {
            selected_location = MAIN_GUN;
            for(int i = 0; i < main_gun_data.size(); i++) {
                Rectangle new_rect = {ppasp.x, (ppasp.y + (i*PURCHASE_HEIGHT)), 400, PURCHASE_HEIGHT};
                purchase_part_areas.push_back(new_rect);
            }
        }
    }
    else if(selected_location == NONE){
        hovered_location = NONE;
        equipped_part_stat_list.header_text = "";
        ClearLabelList(equipped_part_stat_list);
        equipped_part_label.text = "";
        gun_outline_sprite.modulate = GRAY;
        engine_outline_sprite.modulate = GRAY;
        purchase_part_areas.clear();
        hovered_purchase_part_index = -1;
        selected_purchase_part_index = -1;
    }
}

//================================================

void PartsMenu::DrawMainGunPurchaseStats(int index) {
    int cost = main_gun_data[index].cost;
    DrawText( TextFormat("cost\n%iscrap", cost), ppasp.x + 5,  (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, GREEN);

    std::string name = main_gun_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT) + 5), 20, YELLOW);

    float max_power = main_gun_data[index].GUN_MAX_POWER;
    DrawText( TextFormat("max power: %0.2f", max_power), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 30, 20, YELLOW);

    float use = main_gun_data[index].GUN_POWER_USE;
    DrawText( TextFormat("power use: %0.2f", use), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 55, 20, YELLOW);

    float delay = main_gun_data[index].GUN_DELAY;
    DrawText( TextFormat("shot delay: %0.2f", delay), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 80, 20, YELLOW);

    float regen = main_gun_data[index].GUN_REGEN;
    DrawText( TextFormat("power regen: %0.2f", regen), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 110, 20, YELLOW);

    float weight = main_gun_data[index].weight;
    DrawText( TextFormat("weight: %0.2f", weight), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 140, 20, YELLOW);
}

//========================================================

void PartsMenu::DrawThrusterPurchaseStats(int index) {
    int cost = thrusters_data[index].cost;
    DrawText( TextFormat("cost\n%iscrap", cost), ppasp.x + 5,  (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, GREEN);

    std::string name = thrusters_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, YELLOW);

    float speed = thrusters_data[index].THRUSTER_SPEED;
    DrawText( TextFormat("max speed: %0.2f", speed), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 30, 20, YELLOW);

    float turn = thrusters_data[index].THRUSTER_SHIP_ROT_SPEED;
    DrawText( TextFormat("turn speed: %0.2f", turn), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 55, 20, YELLOW);

    float thrust = thrusters_data[index].THRUSTER_SHIP_THRUST;
    DrawText( TextFormat("max thrust: %0.2f", speed), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 80, 20, YELLOW);

    float weight = thrusters_data[index].weight;
    DrawText( TextFormat("wight: %0.2f", weight), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 110, 20, YELLOW);


}