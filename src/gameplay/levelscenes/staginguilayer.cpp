#include "../../core/global_def.h"


StagingUILayer::StagingUILayer() {
    screen_center = { settings.resolution.x/2, settings.resolution.y/2 };

    CreateButton(quit_button, { settings.resolution.x - 40, 20 }, {30, 30}, RED, "X");
    quit_button.default_color = DARKGRAY;

    button_sound = LoadSound("assets/button.wav");
    
    menus_are_open = false;

    CreatePanel(shop_panel, {10, 280}, {300, 300}, Fade(DARKGREEN, 0.1f));
    shop_panel_visible = false;
    parts_visible = false;
    shipyard_visible = false;
    CreateButton(parts_button, {150,320}, {150, 50}, YELLOW, "Parts");
    parts_button.default_color = DARKGRAY;
    CreateButton(shipyard_button, {155,400}, {150, 50}, YELLOW, "Shipyard");
    shipyard_button.default_color = DARKGRAY;
    
    
    CreatePanel(battle_panel, {750, 50}, {500, 350}, Fade(DARKPURPLE, 0.1f));
    battle_panel_visible = false;
    CreateButton(battle_button, {850, 300}, {150, 50}, YELLOW, "To Battle");
    battle_button.default_color = DARKGRAY;

    parts_menu.parts_close.Connect( [&](){OnPartsClosed();} );
    shipyard_menu.shipyard_close.Connect( [&](){OnShipyardClosed();} );

    CreateLabel(scrap_label, {50, 5}, 50, GOLD, "SCRAP:");
    top_bar_rect = {0,0, settings.resolution.x, 50};
    
}

StagingUILayer::~StagingUILayer() {
    UnloadSound(button_sound);
}

void StagingUILayer::Draw() {

    if(shop_panel_visible) {
        DrawShopPanel();
    }

    if(battle_panel_visible) {
        DrawBattlePanel();
    }


    if(parts_visible) {
        parts_menu.Draw();
    }

    if(shipyard_visible) {
        shipyard_menu.Draw();
    }

    DrawRectangleRec(top_bar_rect, DARKGRAY);
    DrawRectangleLines(top_bar_rect.x, top_bar_rect.y, top_bar_rect.width,top_bar_rect.height, RAYWHITE);
    DrawLabel(scrap_label);

    DrawButton(quit_button);
}

void StagingUILayer::Update() {

    if(shop_panel_visible) {
        UpdateShopPanel();
    }

    if(battle_panel_visible) {
        UpdateBattlePanel();
    }

    if(parts_visible) {
        parts_menu.Update();
    }

    if(shipyard_visible) {
        shipyard_menu.Update();
    }

    if(IsButtonHovered(quit_button, settings.game_scale)) {
        if(quit_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            quit_pressed.EmitSignal();
        }
    }

    scrap_label.text = TextFormat("SCRAP: %i", player_data.scrap_amount);
}

void StagingUILayer::ShowShopPanel() {
    shop_panel_visible = true;
}

void StagingUILayer::ShowBattlePanel() {
    battle_panel_visible = true;
}

void StagingUILayer::HideShopPanel() {
    shop_panel_visible = false;
}

void StagingUILayer::HideBattlePanel() {
    battle_panel_visible = false;
}

void StagingUILayer::DrawShopPanel() {
    DrawPanel(shop_panel);
    DrawButton(parts_button);
    DrawButton(shipyard_button);
}

void StagingUILayer::UpdateShopPanel() {
    if(IsButtonHovered(parts_button, settings.game_scale)) {
        if(parts_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            parts_visible = true;
            shop_panel_visible = false;
            menus_are_open = true;
            //parts_pressed.EmitSignal();
        }
    }

    if(IsButtonHovered(shipyard_button, settings.game_scale)) {
        if(shipyard_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            shipyard_visible = true;
            shop_panel_visible = false;
            menus_are_open = true;
        }
    }
}

void StagingUILayer::DrawBattlePanel() {
    DrawPanel(battle_panel);
    DrawButton(battle_button);
}

void StagingUILayer::UpdateBattlePanel() {
    if(IsButtonHovered(battle_button, settings.game_scale)) {
        if(battle_button.already_hovered == false) {
            PlaySound(button_sound);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            battle_pressed.EmitSignal();
        }
    }
}

void StagingUILayer::OnPartsClosed() {
    parts_visible = false;
    menus_are_open = false;
}

void StagingUILayer::OnShipyardClosed() {
    shipyard_visible = false;
    menus_are_open = false;
}