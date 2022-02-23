#include <Keyboard.h>

// use this option for OSX:
char ctrlKey = KEY_LEFT_GUI;
// use this option for Windows and Linux:
//  char ctrlKey = KEY_LEFT_CTRL;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
    
  }
  
}
