#include <stdio.h>
#include <raylib.h>
#include "utils/utils.h"

int main(void) {
   
   Timer timer(5.0);

   InitWindow(300, 300, "cracked");
   Vector2 newvec;
   puts("Hello, you?");



   while(!WindowShouldClose()) {
      timer.Update();
      if(timer.IsDone()) {
         return 0;
      }
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText(TextFormat("%i", (int)timer.TimeRemaining()), 20, 200, 30, BLACK);
      DrawText(TextFormat("%i", (int)timer.TimeElapsed()), 60, 200, 30, BLACK);
      EndDrawing();
   }
   return 0;
}
