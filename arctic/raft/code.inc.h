// Raft
int Raft_x;
int Raft_y;
int score;
int level;
int Up;
int g;
int b;
int r;
int s;
int w;
int h;
int pu;
bool ap;
bool slow;
// Glacier
size_t gk = 30;
int  Glacier_x[gk];
int  Glacier_y[gk];

// Menu
int selected = 0;
const int MainMenuN = 2;
const int GameMenuN = 7;
labelMainMenu:
selected = 0;
while (true) {
  
  Clear(Rgba(128, 56, 255));
  Ink(selected == 0 ? 8 : 1);
  Print(10, 50, "New game!");
  Ink(selected == 1 ? 8 : 1);
  Print(10, 30, "EXIT");

  ShowFrame();

  if (IsKeyDownward(kKeyDown)) {
    selected = (selected + 1) % MainMenuN;
  }
  if (IsKeyDownward(kKeyUp)) {
    selected = (selected - 1 + MainMenuN) % MainMenuN;
  }
  if (IsKeyDownward(kKeyEnter)) {
    switch (selected) {
      case 0: goto labelNewGame;
      case 1: goto labelExit;
    }
  }
}

labelNewGame:
while (true) {
  r = 0;
  Clear(Rgba(128, 56, 255));
  Ink(selected == 0 ? 8 : 1);
  Print(10, 90, "Simple");
  Ink(selected == 1 ? 8 : 1);
  Print(10, 80, "Glow");
  Ink(selected == 2 ? 8 : 1);
  Print(10, 70, "Walking glaciers");
  Ink(selected == 3 ? 8 : 1);
  Print(10, 60, "Fast difficulty");
  Ink(selected == 4 ? 8 : 1);
  Print(10, 50, "Fast difficulty+");
  Ink(selected == 5 ? 8 : 1);
  Print(10, 40, "Fast-walk glaciers");
  Ink(selected == 6 ? 8 : 1);
  Print(10, 30, "Menu");

  ShowFrame();

  if (IsKeyDownward(kKeyDown)) {
    selected = (selected + 1) % GameMenuN;
  }
  if (IsKeyDownward(kKeyUp)) {
    selected = (selected - 1 + GameMenuN) % GameMenuN;
  }
  if (IsKeyDownward(kKeyEnter)) {
    switch (selected) {
      case 0:
        ap = false;
        Raft_x = 50;
        Raft_y = 50;
        score = 0;
        level = 90;
        Up = 1;
        g = 200;
        b = 200;
        r = 0;
        s = 20;
        gk = 25;
        Glacier_x[gk];
        Glacier_y[gk];
        goto labelGame;
      case 1:
        ap = false;
        Raft_x = 100;
        Raft_y = 100;
        score = 0;
        level = 80;
        Up = 1;
        g = 20;
        b = 50;;
        s = 60;
        gk = 35;
        Glacier_x[gk];
        Glacier_y[gk];
        goto labelGame;;
      case 2:
        ap = false;
        Raft_x = 50;
        Raft_y = 50;
        score = 0;
        level = 60;
        Up = 1;
        g = 100;
        b = 150;
        r = 0;
        s = 20;
        gk = 45;
        Glacier_x[gk];
        Glacier_y[gk];
        goto labelGame;;
      case 3:
        ap = true;
        Raft_x = 0;
        Raft_y = 50;
        score = 0;
        level = 60;
        Up = 1;
        g = 0;
        b = 90;
        s = 40;
        gk = 30;
        Glacier_x[gk];
        Glacier_y[gk];
        goto labelGame;;
      case 4:
        slow = true;
        ap = true;
        Raft_x = 0;
        Raft_y = 50;
        score = 0;
        level = 80;
        Up = 1;
        g = Random32(0, 100);
        b = Random32(0, 200);
        s = 20;
        gk = 50;
        Glacier_x[gk];
        Glacier_y[gk];
        goto labelGame;;
      case 5:
        slow = true;
        ap = true;
        Raft_x = 0;
        Raft_y = 50;
        score = 0;
        level = 80;
        Up = 1;
        g = Random32(0, 100);
        b = Random32(0, 200);
        r = g + b;
        s = 20;
        gk = 75;
        Glacier_x[gk];
        Glacier_y[gk];
        goto labelGame;;
      case 6: goto labelMainMenu;;

    }
  }
}
labelGame:
while(true){
    Clear(Rgba(r, g, b));
  
    for (Si32 i = 0; i < gk; i++) {
      int amp = Random32(0, 3);
      if(ap == false){
        Glacier_y[i]--;
      }else{

          if(amp == 0){
            Glacier_y[i]--;
          }
        if(amp == 1){
            Glacier_y[i]--;
            Glacier_x[i]--;
          }
          if(amp == 2){
            Glacier_y[i]++;
            Glacier_x[i]++;
        }
      }
      if (Glacier_y[i] == -1) {
        score++;
        Glacier_y[i] = (Si32)Random(level, 100);
        Glacier_x[i] = (Si32)Random(0, 100);
      }
      Ink(8);
      Plot(Glacier_x[i], Glacier_y[i]);
      
      if ((Glacier_x[i] == Raft_x && Glacier_y[i] == Raft_y) || (Glacier_x[i] == Raft_x && Glacier_y[i] == Raft_y + 1) || (Glacier_x[i] == Raft_x + 1 && Glacier_y[i] == Raft_y) || (Glacier_x[i] == Raft_x + 1 && Glacier_y[i] == Raft_y + 1)) {
        Beep(1,5);
        Beep(1,5);
        Beep(1,5);
        Beep(1,5);
        goto labelMainMenu;
      }
      Ink(12);

      

      if(IsKeyDown(kKeyB) && score >= 350 && Up > 1){
        score -= 350;
        ap = true;
      }
      
      Plot(Raft_x, Raft_y);
      Plot(Raft_x, Raft_y + 1);
      Plot(Raft_x + 1, Raft_y);
      Plot(Raft_x + 1, Raft_y + 1);
    }
  

  
  if(IsKeyDown(kKeyW) || IsKeyDown(kKeyUp) ){
    Raft_y++;
  }
  if(IsKeyDown(kKeyS) || IsKeyDown(kKeyDown)){
    Raft_y--;
  }
  if(IsKeyDown(kKeyD) || IsKeyDown(kKeyRight)){
    Raft_x++;
  }
  if(IsKeyDown(kKeyA) || IsKeyDown(kKeyLeft)){
    Raft_x--;
  }

  
  if(score % 60 == 0){
    if(level <= 0){
      level = 90;
      b = 250;
      g = 250;
    }else{
      level -= 5;
      g -= 10;
      b -= 5;
    }
  }
  if(score >= s){
    for(int i = 0; i == 5; i++){
      Beep(1,0);
    }
    Up += 1;
    s  = Up * 2 * 10;
    score = 0;
    level = 90;
    g = 0;
    b = s * 5;
  }
  Ink(0);
  Print(0, 0, score);

  Ink(10);
  Print(50, 90, Up);
  
  Ink(2);
  Print(60, 0, s);
  
  ShowFrame();
}
    
labelExit:
