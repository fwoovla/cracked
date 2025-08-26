#include "../../core/global_def.h"

#define PURCHASE_HEIGHT 100.0f

PartsMenu::PartsMenu(){

    player_data.scrap_amount = 10;

    screen_center = { settings.resolution.x/2, settings.resolution.y/2 };
    float margin = 100.0f;

    CreateLabel(header, {screen_center.x, margin + 20}, 40, GOLD, "Parts Shop");

    CreatePanel(menu_panel, {margin, margin}, {settings.resolution.x - (margin*2), settings.resolution.y - (margin*2)}, BLACK, 1.0f) ;

    CreateButton(exit_button, { screen_center.x, menu_panel.size.y + margin}, {300, 50}, ORANGE, "back");

    button_sound = LoadSound("assets/button.wav");
    
    LoadSpriteCentered(ship_outline_sprite, LoadTexture("assets/shipoutline.png"), screen_center);
    ScaleSprite(ship_outline_sprite, {2,2});
    
    LoadSpriteCentered(gun_outline_sprite, LoadTexture("assets/gunoutline.png"), {screen_center.x+50, screen_center.y});
    ScaleSprite(gun_outline_sprite, {2,2});
    gun_area = gun_outline_sprite.dest;
    gun_area.x -= (gun_area.width * 0.5f);
    gun_area.y -= (gun_area.height * 0.5f);
    
    LoadSpriteCentered(engine_outline_sprite, LoadTexture("assets/engineoutline.png"), {screen_center.x-150, screen_center.y});
    ScaleSprite(engine_outline_sprite, {2,2});
    engine_area = engine_outline_sprite.dest;
    engine_area.x -= (engine_area.width * 0.5f);
    engine_area.y -= (engine_area.height * 0.5f);

    LoadSpriteCentered(armor_outline_sprite, LoadTexture("assets/armoroutline.png"), {screen_center.x, screen_center.y-150});
    ScaleSprite(armor_outline_sprite, {2,2});
    armor_area = armor_outline_sprite.dest;
    armor_area.x -= (armor_area.width * 0.5f);
    armor_area.y -= (armor_area.height * 0.5f);
    
    CreateButton(part_exit_button, {margin + 300, margin + 60}, {30, 30}, RED, "X");

    CreateLabel(equipped_part_header, {margin + 50, margin + 50}, 30, GRAY, "Equipped Part");
    CreateLabel(equipped_part_label, {margin + 50, margin + 100}, 20, RAYWHITE, "");
    CreateLabelList(equipped_part_stat_list, {margin + 50, margin + 150}, 200, 16, 20, YELLOW, RAYWHITE, "");

    selected_location = NONE;
    hovered_location = NONE;

    ppasp = {settings.resolution.x - 400.0f, margin + 70};
    CreateLabel(shop_header, {ppasp.x, ppasp.y - 30}, 30, GRAY, "Shop");
    hovered_purchase_part_index = -1;
    selected_purchase_part_index = -1;

    CreatePanel(part_detail_panel, {margin + 375, margin + 75}, {325, 400}, {10,10,30,255});

    CreateButton(part_buy_button, { part_detail_panel.position.x + (part_detail_panel.size.x/2), part_detail_panel.position.y + part_detail_panel.size.y - 50}, {200, 50}, GREEN, "buy");

    CreateLabel(buy_info_label, {part_detail_panel.position.x + (part_detail_panel.size.x/2), part_detail_panel.position.y + part_detail_panel.size.y - 100}, 20, ORANGE, "");
    info_label_timer = new Timer(2.5, false, true);
    info_label_timer->timout.Connect( [&](){OnInfoLabelTimerTimeout();} );

    CreateLabel(armor_label, {margin + 50, margin + 300}, 24, RAYWHITE, "Armor: ");
    CreateLabel(capacity_label, {margin + 50, margin + 340}, 24, RAYWHITE, "Ship Capacity: ");
}

PartsMenu::~PartsMenu() {
    delete info_label_timer;
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
    DrawSprite(armor_outline_sprite);
    
    DrawButton(exit_button);
    DrawLabelCentered(header);

    DrawLabel(armor_label);
    DrawLabel(capacity_label);
    
    DrawLabel(equipped_part_header);
    DrawLabel(equipped_part_label);
    DrawLabelList(equipped_part_stat_list);
    
    if(selected_location != NONE) {
        DrawLabel(shop_header);
        DrawButton(part_exit_button);

        for(int i = 0; i < purchase_part_areas.size(); i++) {
            if(selected_location == MAIN_GUN_LOCATION) {
                if(hovered_purchase_part_index == i) {
                    if(player_data.scrap_amount >= main_gun_data[i].cost) {
                         DrawRectangleRec( purchase_part_areas[i], Fade(GREEN, 0.2) );
                    }
                    else {
                         DrawRectangleRec( purchase_part_areas[i], Fade(RED, 0.2) );
                    }
                }
                DrawMainGunPurchaseStats(i);
            }
            if(selected_location == THRUSTERS_LOCATION) {
                if(hovered_purchase_part_index == i) {
                    if(player_data.scrap_amount >= thrusters_data[i].cost) {
                         DrawRectangleRec( purchase_part_areas[i], Fade(GREEN, 0.2) );
                    }
                    else {
                         DrawRectangleRec( purchase_part_areas[i], Fade(RED, 0.2) );
                    }
                }
                DrawThrusterPurchaseStats(i);
            }
            if(selected_location == ARMOR_LOCATION) {
                if(hovered_purchase_part_index == i) {
                    if(player_data.scrap_amount >= armors_data[i].cost) {
                         DrawRectangleRec( purchase_part_areas[i], Fade(GREEN, 0.2) );
                    }
                    else {
                         DrawRectangleRec( purchase_part_areas[i], Fade(RED, 0.2) );
                    }
                }
                DrawArmorPurchaseStats(i);
            }
        }
    }
    if(selected_purchase_part_index != -1) {
        DrawPanel(part_detail_panel);
        if(selected_location == MAIN_GUN_LOCATION) {
            DrawMainGunStats(selected_purchase_part_index);
        }
        if(selected_location == THRUSTERS_LOCATION) {
            DrawThrusterStats(selected_purchase_part_index);
        }
        if(selected_location == ARMOR_LOCATION) {
            DrawArmorStats(selected_purchase_part_index);
        }
        DrawButton(part_buy_button);
    }
    DrawLabelCentered(buy_info_label);
}


void PartsMenu::Update()
{

    float dt = GetFrameTime();
    float sc = settings.game_scale;
    UpdatePanel(menu_panel);
    info_label_timer->Update();
    armor_label.text = TextFormat("Armor: %i", player_data.health);
    capacity_label.text = TextFormat("Ship Capacity: %0.2f", player_data.capacity);

    if(IsButtonHovered(exit_button, settings.game_scale)) {
        if(exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            parts_close.EmitSignal();
            ResetPanel(menu_panel);
            ClearAll();
        }
    }

    if(IsButtonHovered(part_exit_button, settings.game_scale)) {
        if(part_exit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ClearAll();
        }
    } 

    if(selected_location != NONE) {
        hovered_purchase_part_index = -1;

        for(int i = 0; i < purchase_part_areas.size(); i++) {
            if(CheckCollisionPointRec(GetMousePosition(), { purchase_part_areas[i].x*sc, purchase_part_areas[i].y*sc, purchase_part_areas[i].width*sc, purchase_part_areas[i].height*sc } )) {
                hovered_purchase_part_index =i;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    //TraceLog(LOG_INFO, "part clicked %i", i);
                    selected_purchase_part_index = i;
                }
            }
        }

        if(selected_purchase_part_index != -1) {
            int cost = 1000000;
            float weight = 0.0;

            if(selected_location == MAIN_GUN_LOCATION) { 
                cost = main_gun_data[selected_purchase_part_index].cost;
                weight = main_gun_data[selected_purchase_part_index].weight;
            }
            if(selected_location == THRUSTERS_LOCATION) {
                cost = thrusters_data[selected_purchase_part_index].cost;
                weight = thrusters_data[selected_purchase_part_index].weight;
            }
            if(selected_location == ARMOR_LOCATION) {
                cost = armors_data[selected_purchase_part_index].cost;
                weight = armors_data[selected_purchase_part_index].weight;
            }

            if(player_data.scrap_amount >= cost) {
                part_buy_button.focus_color = GREEN;
            }
            else {
                part_buy_button.focus_color = RED;
            }

            if(IsButtonHovered(part_buy_button, settings.game_scale)) {
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    //TraceLog(LOG_INFO, "BUY PART");
//================================================main gun===============================================
                    if(selected_location == MAIN_GUN_LOCATION and player_data.scrap_amount >= cost and player_data.capacity > weight) {
                        ClearLabelList(equipped_part_stat_list);
                        player_data.scrap_amount -= main_gun_data[selected_purchase_part_index].cost;
                        
                        player_data.main_gun_part.part_name = main_gun_data[selected_purchase_part_index].part_name;
                        player_data.main_gun_part.cost =  main_gun_data[selected_purchase_part_index].cost;
                        player_data.main_gun_part.GUN_MAX_POWER =  main_gun_data[selected_purchase_part_index].GUN_MAX_POWER;
                        player_data.main_gun_part.GUN_POWER_USE =  main_gun_data[selected_purchase_part_index].GUN_POWER_USE;
                        player_data.main_gun_part.GUN_DELAY =  main_gun_data[selected_purchase_part_index].GUN_DELAY;
                        player_data.main_gun_part.GUN_REGEN =  main_gun_data[selected_purchase_part_index].GUN_REGEN;
                        player_data.main_gun_part.weight =  main_gun_data[selected_purchase_part_index].weight;
                        
                        equipped_part_stat_list.header_text = player_data.main_gun_part.part_name.c_str();
                        AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.main_gun_part.weight) );
                        AddLabelToList(equipped_part_stat_list, TextFormat("power %.2f", player_data.main_gun_part.GUN_POWER_USE) );
                        AddLabelToList(equipped_part_stat_list, TextFormat("shot delay %.2f", player_data.main_gun_part.GUN_DELAY) );

                        selected_purchase_part_index = -1;
                    }
                    else if(selected_location == MAIN_GUN_LOCATION and player_data.scrap_amount < cost) {
                        buy_info_label.text = "NOT ENOUGH SCRAP";
                        info_label_timer->Start();
                    }
                    else if(selected_location == MAIN_GUN_LOCATION and player_data.capacity < weight) {
                        buy_info_label.text = "NOT ENOUGH ROOM";
                        info_label_timer->Start();
                    }

//================================================thrusters===============================================
                    if(selected_location == THRUSTERS_LOCATION and player_data.scrap_amount >= cost and player_data.capacity > weight) {
                        ClearLabelList(equipped_part_stat_list);
                        player_data.scrap_amount -= thrusters_data[selected_purchase_part_index].cost;
                        
                        player_data.thrusters_part.part_name = thrusters_data[selected_purchase_part_index].part_name;
                        player_data.thrusters_part.cost =  thrusters_data[selected_purchase_part_index].cost;
                        player_data.thrusters_part.THRUSTER_SHIP_THRUST =  thrusters_data[selected_purchase_part_index].THRUSTER_SHIP_THRUST;
                        player_data.thrusters_part.THRUSTER_SPEED =  thrusters_data[selected_purchase_part_index].THRUSTER_SPEED;
                        player_data.thrusters_part.THRUSTER_SHIP_ROT_SPEED =  thrusters_data[selected_purchase_part_index].THRUSTER_SHIP_ROT_SPEED;
                        player_data.thrusters_part.weight =  thrusters_data[selected_purchase_part_index].weight;
                        
                        equipped_part_stat_list.header_text = player_data.thrusters_part.part_name.c_str();
                        AddLabelToList(equipped_part_stat_list, TextFormat("top speed %.2f", player_data.thrusters_part.THRUSTER_SPEED) );
                        AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.thrusters_part.weight) );
                        
                        selected_purchase_part_index = -1;
                    }
                    else if(selected_location == THRUSTERS_LOCATION and cost) {
                        buy_info_label.text = "NOT ENOUGH SCRAP";
                        info_label_timer->Start();
                    }
                    else if(selected_location == THRUSTERS_LOCATION and weight) {
                        buy_info_label.text = "NOT ENOUGH ROOM";
                        info_label_timer->Start();
                    }
//================================================armor===============================================
                    if(selected_location == ARMOR_LOCATION and player_data.scrap_amount >= cost and player_data.capacity > weight) {
                        ClearLabelList(equipped_part_stat_list);
                        player_data.scrap_amount -= armors_data[selected_purchase_part_index].cost;
                        
                        player_data.armor_part.part_name = armors_data[selected_purchase_part_index].part_name;
                        player_data.armor_part.cost =  armors_data[selected_purchase_part_index].cost;
                        player_data.armor_part.ARMOR =  armors_data[selected_purchase_part_index].ARMOR;
                        player_data.armor_part.weight =  armors_data[selected_purchase_part_index].weight;
                        
                        
                        equipped_part_stat_list.header_text = player_data.thrusters_part.part_name.c_str();
                        AddLabelToList(equipped_part_stat_list, TextFormat("armor %i", player_data.armor_part.ARMOR) );
                        AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.armor_part.weight) );
                        
                        selected_purchase_part_index = -1;
                    }
                    else if(selected_location == ARMOR_LOCATION and player_data.scrap_amount < cost) {
                        buy_info_label.text = "NOT ENOUGH SCRAP";
                        info_label_timer->Start();
                    }
                    else if(selected_location == ARMOR_LOCATION and player_data.capacity < weight) {
                        buy_info_label.text = "NOT ENOUGH ROOM";
                        info_label_timer->Start();
                    }
                }
            }
        }
    }

    if(CheckCollisionPointRec(GetMousePosition(), {engine_area.x*sc, engine_area.y*sc, engine_area.width*sc, engine_area.height*sc })) {
        if(hovered_location != THRUSTERS_LOCATION and selected_location == NONE) {
            hovered_location = THRUSTERS_LOCATION;
            engine_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "THRUSTERS";
            equipped_part_stat_list.header_text = player_data.thrusters_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("top speed %.2f", player_data.thrusters_part.THRUSTER_SPEED) );
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.thrusters_part.weight) );
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and selected_location == NONE) {
            selected_location = THRUSTERS_LOCATION;
            for(int i = 0; i < thrusters_data.size(); i++) {
                Rectangle new_rect = {ppasp.x, (ppasp.y + (i*PURCHASE_HEIGHT)), 300, PURCHASE_HEIGHT};
                purchase_part_areas.push_back(new_rect);
                //TraceLog(LOG_INFO, "ITEM %i", i);
            }
        }
    }
    else if(CheckCollisionPointRec(GetMousePosition(), {gun_area.x*sc, gun_area.y*sc, gun_area.width*sc, gun_area.height*sc })) {
        if(hovered_location != MAIN_GUN_LOCATION and selected_location == NONE) {
            hovered_location = MAIN_GUN_LOCATION;
            gun_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "MAIN GUN";
            equipped_part_stat_list.header_text = player_data.main_gun_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.main_gun_part.weight) );
            AddLabelToList(equipped_part_stat_list, TextFormat("power %.2f", player_data.main_gun_part.GUN_POWER_USE) );
            AddLabelToList(equipped_part_stat_list, TextFormat("shot delay %.2f", player_data.main_gun_part.GUN_DELAY) );
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and selected_location == NONE) {
            selected_location = MAIN_GUN_LOCATION;
            for(int i = 0; i < main_gun_data.size(); i++) {
                Rectangle new_rect = {ppasp.x, (ppasp.y + (i*PURCHASE_HEIGHT)), 300, PURCHASE_HEIGHT};
                purchase_part_areas.push_back(new_rect);
            }
        }
    }
    else if(CheckCollisionPointRec(GetMousePosition(), {armor_area.x*sc, armor_area.y*sc, armor_area.width*sc, armor_area.height*sc })) {
        if(hovered_location != ARMOR_LOCATION and selected_location == NONE) {
            hovered_location = ARMOR_LOCATION;
            armor_outline_sprite.modulate = ORANGE;
            equipped_part_label.text = "ARMOR";
            equipped_part_stat_list.header_text = player_data.armor_part.part_name.c_str();
            AddLabelToList(equipped_part_stat_list, TextFormat("weight %.2f", player_data.armor_part.weight) );
            AddLabelToList(equipped_part_stat_list, TextFormat("power %.2f", player_data.armor_part.ARMOR) );
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) and selected_location == NONE) {
            selected_location = ARMOR_LOCATION;
            for(int i = 0; i < armors_data.size(); i++) {
                Rectangle new_rect = {ppasp.x, (ppasp.y + (i*PURCHASE_HEIGHT)), 300, PURCHASE_HEIGHT};
                purchase_part_areas.push_back(new_rect);
            }
        }
    }
    else if(selected_location == NONE){
        ClearAll();
    }
}

void PartsMenu::ClearAll() {
    selected_location = NONE;
    hovered_location = NONE;
    equipped_part_stat_list.header_text = "";
    ClearLabelList(equipped_part_stat_list);
    equipped_part_label.text = "";
    gun_outline_sprite.modulate = GRAY;
    engine_outline_sprite.modulate = GRAY;
    armor_outline_sprite.modulate = GRAY;
    purchase_part_areas.clear();
    hovered_purchase_part_index = -1;
    selected_purchase_part_index = -1;
}

//================================================

void PartsMenu::DrawMainGunPurchaseStats(int index) {
    int cost = main_gun_data[index].cost;
    DrawText( TextFormat("cost\n%i scrap", cost), ppasp.x + 5,  (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, GREEN);

    std::string name = main_gun_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT) + 5), 20, YELLOW);

}

//========================================================

void PartsMenu::DrawThrusterPurchaseStats(int index) {
    int cost = thrusters_data[index].cost;
    DrawText( TextFormat("cost\n%i scrap", cost), ppasp.x + 5,  (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, GREEN);

    std::string name = thrusters_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, YELLOW);

}

//========================================================

void PartsMenu::DrawArmorPurchaseStats(int index) {
    int cost = armors_data[index].cost;
    DrawText( TextFormat("cost\n%i scrap", cost), ppasp.x + 5,  (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, GREEN);

    std::string name = armors_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), ppasp.x+100, (ppasp.y + (index*PURCHASE_HEIGHT)) + 5, 20, YELLOW);

}


void PartsMenu::DrawMainGunStats(int index) {
    std::string name = main_gun_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), part_detail_panel.position.x + 5, part_detail_panel.position.y + 5, 30, YELLOW);

    int cost = main_gun_data[index].cost;
    DrawText( TextFormat("cost: %i scrap", cost), part_detail_panel.position.x + 5,  part_detail_panel.position.y + 35, 24, GREEN);

    float max_power = main_gun_data[index].GUN_MAX_POWER;
    DrawText( TextFormat("max power: %0.2f", max_power), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 100, 20, YELLOW);
    float use = main_gun_data[index].GUN_POWER_USE;
    DrawText( TextFormat("power use: %0.2f", use), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 125, 20, YELLOW);

    float delay = main_gun_data[index].GUN_DELAY;
    DrawText( TextFormat("shot delay: %0.2f", delay), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 150, 20, YELLOW);

    float regen = main_gun_data[index].GUN_REGEN;
    DrawText( TextFormat("power regen: %0.2f /s", regen), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 175, 20, YELLOW);

    float weight = main_gun_data[index].weight;
    DrawText( TextFormat("weight: %0.2f", weight), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 200, 20, YELLOW);

}

void PartsMenu::DrawThrusterStats(int index) {
    std::string name = thrusters_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), part_detail_panel.position.x + 5, part_detail_panel.position.y + 5, 30, YELLOW);

    int cost = thrusters_data[index].cost;
    DrawText( TextFormat("cost: %i scrap", cost), part_detail_panel.position.x + 5,  part_detail_panel.position.y + 35, 24, GREEN);

    float speed = thrusters_data[index].THRUSTER_SPEED;
    DrawText( TextFormat("max speed: %0.2f", speed), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 100, 20, YELLOW);

    float turn = thrusters_data[index].THRUSTER_SHIP_ROT_SPEED;
    DrawText( TextFormat("turn speed: %0.2f /s", turn), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 125, 20, YELLOW);

    float thrust = thrusters_data[index].THRUSTER_SHIP_THRUST;
    DrawText( TextFormat("max thrust: %0.2f", speed), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 150, 20, YELLOW);

    float weight = thrusters_data[index].weight;
    DrawText( TextFormat("weight: %0.2f", weight), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 175, 20, YELLOW);
}

void PartsMenu::DrawArmorStats(int index) {
    std::string name = armors_data[index].part_name;
    DrawText( TextFormat("%s", name.c_str()), part_detail_panel.position.x + 5, part_detail_panel.position.y + 5, 30, YELLOW);

    int cost = armors_data[index].cost;
    DrawText( TextFormat("cost: %i scrap", cost), part_detail_panel.position.x + 5,  part_detail_panel.position.y + 35, 24, GREEN);

    int armor = armors_data[index].ARMOR;
    DrawText( TextFormat("max armor: %i", armor), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 100, 20, YELLOW);

    float weight = armors_data[index].weight;
    DrawText( TextFormat("weight: %0.2f", weight), part_detail_panel.position.x + 15,  part_detail_panel.position.y + 125, 20, YELLOW);

}

void PartsMenu::OnInfoLabelTimerTimeout() {
    buy_info_label.text = "";
}