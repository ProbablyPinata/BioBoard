#include <Keyboard.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);

  Keyboard.begin();
}

int cols[] = {9, 8, 7};
int rows[] = {A1, A2, A3};


char keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9' }; 
// Bitmask

uint16_t prev_mask = 0x0, curr_mask = 0x0;


void loop() {
  // put your main code here, to run repeatedly:
  for (int c = 0; c < 3; c++) {
    digitalWrite(cols[c], HIGH);

    for (int r = 0; r < 3; r++) {
      if (digitalRead(rows[r]) == HIGH) {
        Serial.print("Row ");
        Serial.print(r);
        Serial.print(" Column ");
        Serial.print(c);
        Serial.println(" pressed");
        curr_mask |= (unsigned int)((unsigned int)0x1 << (r * 3 + c));
      }

    }
    digitalWrite(cols[c], LOW);

  }
  for (int i = 0; i < 16; i++) {
    if (curr_mask >> i & 0x1) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
  }
  Serial.print("\n");
  // Find which keys to press

  uint16_t new_mask = (~prev_mask) & curr_mask;
  uint16_t old_mask = prev_mask & (~curr_mask);
  for (int i = 0; i < 9; i++) {
    if (old_mask >> i & 0x1) {
      Keyboard.release(keys[i]);
    }
  }
  for (int i = 0; i < 9; i++) {
    if (new_mask >> i & 0x1) {
      Keyboard.press(keys[i]);
    }
  }
  //
  //
  //
  
  
  for (int i = 0; i < 16; i++) {
    if (curr_mask >> i & 0x1) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
  }

  prev_mask = curr_mask;
  curr_mask = 0x0;
}
//
