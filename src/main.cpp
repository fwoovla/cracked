#include <stdio.h>
#include <raylib.h>
#include "globals.h"
#include "utils/utils.h"
#include "core/game.h"

int main(int argc, char *argv[]) {

   gameSettings game_settings;
   game_settings.show_debug = true;
   game_settings.window_size = {1280, 720};

   InitWindow(game_settings.window_size.x, game_settings.window_size.y, "cracked");
   SetTargetFPS(60);

   Game game(game_settings);
   game.StartGame();

   TraceLog(LOG_INFO, "GAME OVER");

   return 0;
}
