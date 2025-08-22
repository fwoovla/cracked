#include <stdio.h>
#include "core/global_def.h"

/* #include <raylib.h>
#include "globals.h"
#include "utils/utils.h"
#include "core/game.h"
 */

gameSettings settings = {
   .window_size = {1920, 1084},
   .resolution = {1280, 720}, // center is 640, 360
   .show_debug = false,
   .control_type = 0,
   .level_num = 1,
};

int main(int argc, char *argv[]) {

   InitWindow(settings.window_size.x, settings.window_size.y, "cracked");
   
   int display = GetCurrentMonitor();
   SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
   ToggleFullscreen();
   InitAudioDevice();
   SetTargetFPS(60);

   settings.starting_position = { (float)GetScreenWidth()/2, (float)GetScreenHeight() /2};

   Game game;
   game.StartGame();
   TraceLog(LOG_INFO, "GAME OVER");

   return 0;
}
