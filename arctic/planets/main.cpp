#include "engine/easy.h"
#include "engine/unicode.h"
using namespace arctic;

bool g_debugFrames = true;

Si32 g_ink = 8;
Vec2Si32 g_pos(0, 0);
Vec2Si32 g_text_pos(0, 0);
Font g_font;

std::vector<Rgba> g_colors = {
  Rgba{0, 0, 0, 255},      // 0=Black
  Rgba{255, 0, 0, 255},    // 1=Red
  Rgba{255, 165, 0, 255},  // 2=Orange
  Rgba{255, 255, 0, 255},  // 3=Yellow
  Rgba{0, 165, 0, 255},    // 4=Green
  Rgba{0, 165, 255, 255},  // 5=Cyan
  Rgba{0, 0, 255, 255},    // 6=Blue
  Rgba{75, 0, 130, 255},   // 7=Violet
  Rgba{255, 255, 255, 255},// 8=White
  Rgba{165, 165, 165, 255},// 9=Gray
  Rgba{90, 90, 90, 255},   // 10=Dark gray
  Rgba{191, 0, 0, 255},    // 11=Dark red
  Rgba{191, 124, 0, 255},  // 12=Dark orange
  Rgba{191, 191, 0, 255},  // 13=Dark yellow
  Rgba{0, 124, 0, 255},    // 14=Dark green
  Rgba{0, 124, 191, 255},  // 15=Dark cyan
  Rgba{0, 0, 191, 255},    // 16=Dark blue
  Rgba{56, 0, 97, 255},    // 17=Dark violet
  Rgba{191, 191, 191, 255},// 18=Dark white
  Rgba{124, 124, 124, 255},// 19=Middle gray
};

void Ink(Si32 color_index) {
  g_ink = std::min(std::max(color_index, 0), (Si32)g_colors.size() - 1);
}

void Plot(Si32 x, Si32 y) {
  g_pos.x = x;
  g_pos.y = y;
  SetPixel(g_pos.x, g_pos.y, g_colors[g_ink]);
}

void Draw(Si32 x, Si32 y) {
  DrawLine(g_pos, Vec2Si32(x, y), g_colors[g_ink]);
  g_pos.x = x;
  g_pos.y = y;
}

void Circle(Si32 x, Si32 y, float r) {
  for (Si32 i = 0; i < 1024; ++i) {
    float alpha = (float)i * (1.f / 1024.f * M_PI * 2.f);
    float s = std::sin(alpha) * r;
    float c = std::cos(alpha) * r;
    SetPixel(x + c + 0.5f, y + s + 0.5f, g_colors[g_ink]);
  }
}

void Fill(Si32 x, Si32 y) {
  Rgba c = GetPixel(x, y);
  if (c == g_colors[g_ink]) {
    return;
  }
  Vec2Si32 screen_size = ScreenSize();
  std::vector<Vec2Si32> next;
  next.reserve(screen_size.x * screen_size.y);
  next.emplace_back(x, y);
  while (!next.empty()) {
    Vec2Si32 p = next.back();
    next.pop_back();
    for (Si32 dx = -1; dx < 2; ++dx) {
      for (Si32 dy = -1; dy < 2; ++dy) {
        Vec2Si32 np(p.x + dx, p.y + dy);
        if (np.x >= 0 && np.x < screen_size.x &&
            np.y >= 0 && np.y < screen_size.y) {
          if (GetPixel(np.x, np.y) == c) {
            SetPixel(np.x, np.y, g_colors[g_ink]);
            next.push_back(np);
          }
        }
      }
    }
  }
}

void Print(Si32 x, Si32 y, std::string text) {
  if (g_font.IsEmpty()) {
    g_font.LoadLetterBits(g_tiny_font_letters, 6, 8);
  }
  g_font.Draw(GetEngine()->GetBackbuffer(), text.c_str(),
              x, y,
              kTextOriginFirstBase,
              kDrawBlendingModeColorize,
              kFilterNearest,
              g_colors[g_ink]);
  g_text_pos.x = x;
  g_text_pos.y = y - g_font.EvaluateSize(text.c_str(), false).y;
}

void Print(Si32 x, Si32 y, Si32 value) {
  char buffer[1024];
  sprintf(buffer, "%d", value);
  Print(x, y, buffer);
}

void Print(Si32 x, Si32 y, double value) {
  char buffer[1024];
  sprintf(buffer, "%f", value);
  Print(x, y, buffer);
}

void Print(std::string text) {
  Print(g_text_pos.x, g_text_pos.y, text);
}

void Print(Si32 value) {
  Print(g_text_pos.x, g_text_pos.y, value);
}

void Print(double value) {
  Print(g_text_pos.x, g_text_pos.y, value);
}

std::string Input(Si32 x, Si32 y, std::string text) {
  Sprite prev_backbuffer;
  prev_backbuffer.Clone(GetEngine()->GetBackbuffer());
  prev_backbuffer.ClearOpaqueSpans();
  std::string input = "";
  Vec2Si32 prev_text_pos = g_text_pos;
  while(true) {
    ShowFrame();
    for (Si32 i = 0; i < InputMessageCount(); ++i) {
      const InputMessage &msg = GetInputMessage(i);
      if (msg.kind == arctic::InputMessage::kKeyboard) {
        if (msg.keyboard.key_state == 1) {
          Ui32 key = msg.keyboard.key;
          if (key == kKeyBackspace) {
            if (!input.empty()) {
              input.pop_back();
              while (!input.empty() && (input.back() & 128) && (input.back() & 64)) {
                input.pop_back();
              }
            }
          } else if (key == kKeyEnter) {
            Clear();
            g_text_pos = prev_text_pos;
            prev_backbuffer.Draw(0, 0, kDrawBlendingModeCopyRgba);
            Print(x, y, text + input);
            return input;
          } else {
            if (msg.keyboard.characters[0]) {
              input.append(msg.keyboard.characters);
            }
          }
        }
      }
    }
    Clear();
    g_text_pos = prev_text_pos;
    prev_backbuffer.Draw(0, 0, kDrawBlendingModeCopyRgba);
    Print(x, y, text + input + (std::fmod(Time(), 0.66) > 0.33 ? "_" : "") );
  }
}

std::string Input(std::string text) {
  return Input(g_text_pos.x, g_text_pos.y, text);
}

double Number(std::string text) {
  double result = 0.0;
  double sign = 1.0;
  bool is_fract = false;
  double fract_mul = 0.1;
  size_t size = text.size();
  if (size == 0) {
    return result;
  }
  size_t i = 0;
  if (text[i] == '-') {
    sign = -1.0;
    ++i;
  }
  while (i < size) {
    char ch = text[i];
    if (ch == '.' || ch == ',') {
      is_fract = true;
    } else if (ch >= '0' && ch <= '9') {
      if (is_fract) {
        result = result + fract_mul * double(ch - '0');
        fract_mul *= 0.1;
      } else {
        result = result * 10.0 + double(ch - '0');
      }
    } else {
      break;
    }
    ++i;
  }
  return result * sign;
}

// Planets
constexpr int planet_count = 3;
int planet_ships[planet_count] = {0}; // кол-во кораблей на планете
int planet_type[planet_count] = {0}; // 0 - обычная, 1 - кольцевая
int planet_owner[planet_count] = {0}; // 0 - не занята, 1 - вы, 2 - враг
int planet_x[planet_count] = {0};
int planet_y[planet_count] = {0};

// Ships
constexpr int ship_count = 1000;
int ship_fly_x[ship_count] = {0};
int ship_fly_y[ship_count] = {0};
int ship_owner[ship_count] = {0}; // 0 - нет, 1 - вы, 2 - враг
int ship_x[ship_count] = {0};
int ship_y[ship_count] = {0};
int t = 0;

// Selection
int sel_x1 = 100;
int sel_y1 = 100;
int sel_x2 = 200;
int sel_y2 = 200;


void EasyMain() {
  ResizeScreen(800, 500);

  planet_owner[0] = 1;
  planet_x[0] = 800 / 2  - 150;
  planet_y[0] = 500 / 2  - 150;

  planet_owner[1] = 0;
  planet_x[1] = 800 / 2;
  planet_y[1] = 500 / 2;

  planet_owner[2] = 2;
  planet_x[2] = 800 / 2  + 150;
  planet_y[2] = 500 / 2  + 150;

  ship_owner[0] = 1;
  ship_x[0] = 800 / 2 - 10;
  ship_y[0] = 500 / 2 + 100;

  ship_owner[1] = 2;
  ship_x[1] = 800 / 2 + 10;
  ship_y[1] = 500 / 2 + 100;  

  while (!IsKeyDownward(kKeyEscape)) {
    // Selection
    sel_x1 = MousePos().x;
    sel_y1 = MousePos().y;
    sel_x2 = MousePos().x + 100;
    sel_y2 = MousePos().y + 100;

    // Rendering
    Clear(Rgba(0xff110000));
    DrawLine(Vec2Si32(sel_x1, sel_y1), Vec2Si32(sel_x1, sel_y1 + 100), Rgba(0, 0, 255));
    DrawLine(Vec2Si32(sel_x1, sel_y1 + 100), Vec2Si32(sel_x2, sel_y2), Rgba(0, 0, 255));
    DrawLine(Vec2Si32(sel_x2, sel_y2), Vec2Si32(sel_x2, sel_y2 - 100), Rgba(0, 0, 255));
    DrawLine(Vec2Si32(sel_x2, sel_y2 - 100), Vec2Si32(sel_x1, sel_y1), Rgba(0, 0, 255));
  
    for (int i = 0; i < planet_count; i++) {
      if (planet_owner[i] == 0) {
        Ink(9);
      } else if (planet_owner[i] == 1) {
        Ink(5);
      } else {
        Ink(1);
      }
      Circle(planet_x[i], planet_y[i], 30);
      Fill(planet_x[i], planet_y[i]);
    }
    for (int i = 0; i < ship_count; i++) {
      if (ship_owner[i] == 0) {
        continue;
      } else if (ship_owner[i] == 1) {
        Ink(15);
      } else {
        Ink(11);
      }
      Plot(ship_x[i], ship_y[i]);
      Plot(ship_x[i]+1, ship_y[i]);
      Plot(ship_x[i], ship_y[i]+1);
      Plot(ship_x[i]-1, ship_y[i]);
      Plot(ship_x[i], ship_y[i]-1);
    }
    if (g_debugFrames) {
      Ink(8);
      Print(50, 50,"Кадр");
      Print(50 + 40, 50,t);
    }
    ShowFrame();
    Sleep(0.032);

    // Physics
    for (int i = 0; i < planet_count; i++) {
      if (planet_owner[i] == 0) {
        continue; // skip neutral planets
      }
      if (t % 100 == 0) {
        // Find dead ship
        for (int j = 0; j < ship_count; j++) {
          if (ship_owner[j] == 0) {
            // Create ship
            ship_owner[j] = planet_owner[i];
            ship_x[j] = planet_x[i] + Random32(-30, 30);
            ship_y[j] = planet_y[i] + Random32(-30, 30);
            break;
          }
        }
      }
    }
    t++;
  }
}
