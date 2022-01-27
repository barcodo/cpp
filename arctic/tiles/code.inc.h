
const size_t width = 9;
const size_t height = 9;
int cells[height][width] = {0}; // 0=empty 1=red 2=blue

// XXXX
// YYYY
// ZZZZ
// WWWW

// XXXXYYYYZZZZWWWW по строчно --- cells[y][x]
// XYZWXYZWXYZWXYZW по колонкам --- cells[x][y]




while (!IsKeyDownward(kKeyEscape)) {
    Clear();
    // [y][x] --> x:y
    // [0][0] --> 0:8
    // [0][1] --> 1:8
    // [1][0] --> 0:7
    // [8][8] --> 8:0
    
    // t = 8; t--;
    
    // f(0) = 8;
    // f(1) = 7;
    // f(2) = 6;
    // f(8) = 0;
    // f(x) = ?;
    
    for (int iy = 0; iy < 9; iy++) {
        for (int ix = 0; ix < 9; ix++) {
            switch (cells[iy][ix]) {
                case 0:
                    Ink(8);
                    break;
                case 1:
                    Ink(1);
                    break;
                case 2:
                    Ink(6);
                    break;
            }
            //Plot(ix * 10, 100 - iy * 10);
            Rect(ix * 10    , 100 - iy * 10 - 8,
                 ix * 10 + 8, 100 - iy * 10    );
        }
    }
    ShowFrame();
    
    Vec2Si32 m = MousePos();
    Si32 ix = m.x / 10;
    Si32 iy = 9 - m.y / 10;
    if (IsKeyDownward(kKeyMouseLeft)) {
        cells[iy][ix] = 2;
    }
    if (IsKeyDownward(kKeyMouseRight)) {
        cells[iy][ix] = 1;
    }
}
