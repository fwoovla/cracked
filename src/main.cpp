#include <stdio.h>


#include "core/global_def.h"

/* #include <raylib.h>
#include "globals.h"
#include "utils/utils.h"
#include "core/game.h"
 */

gameSettings settings = {
   .window_size = {1280, 720},
   .show_debug = false,
   .control_type = 0
};

int main(int argc, char *argv[]) {

   InitWindow(settings.window_size.x, settings.window_size.y, "cracked");
   
   int display = GetCurrentMonitor();
   SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
   ToggleFullscreen();
   InitAudioDevice();
   SetTargetFPS(60);

   Game game;
   game.StartGame();
   TraceLog(LOG_INFO, "GAME OVER");

   return 0;
}
