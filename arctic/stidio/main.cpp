// Copyright (c) <year> Your name

#include "engine/easy.h"

using namespace arctic;  // NOLINT

Font g_font;
int red = 0;
int green = 0;
int blue = 0;
int x = 100;
int y = 100;
int size = 25;

void EasyMain() {
  g_font.Load("data/arctic_one_bmf.fnt");
  DrawRectangle(Vec2Si32(0, 0), Vec2Si32(10000,10000), Rgba(255, 255, 255));
  while (!IsKeyDownward(kKeyEscape)) {
      // Red
          if(IsKeyDown(kKeyR)){
              red++;
          }
          if(IsKeyDown(kKeyT)){
              red--;
          }
      // Green
          if(IsKeyDown(kKeyG)){
            green++;
          }
          if(IsKeyDown(kKeyH)){
              green--;
          }
      // Blue
          if(IsKeyDown(kKeyB)){
              blue++;
          }
          if(IsKeyDown(kKeyN)){
              blue--;
          }
      // Move or Draw
      if(IsKeyDown(kKeyW) || IsKeyDown(kKeyUp)){
          y++;
      }
      if(IsKeyDown(kKeyS) || IsKeyDown(kKeyDown)){
          y--;
      }
      if(IsKeyDown(kKeyA) || IsKeyDown(kKeyLeft)){
          x--;
      }
      if(IsKeyDown(kKeyD) || IsKeyDown(kKeyRight)){
          x++;
      }
      
      if(IsKeyDown(kKeyP)){
          SetPixel(x + 10, y, Rgba(Random(0, 200), Random(0, 200), Random(0, 200)));
      }
      
      DrawCircle(Vec2Si32(x, y), size, Rgba(red, green, blue));
      ShowFrame();
  }
}
