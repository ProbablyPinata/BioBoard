#include <Keyboard.h>
//4444444444444444444444444444444444444444444444444444444444444444444444444444444444
#define THRESHOLD_UP 10
int cols[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int rows[] = {A0, A1, A2, A3, A4};
void setup() {//0000000000000000000000
  // put your setup code here, to run once:
  for (int r = 0; r < sizeof(rows) / sizeof(int); r++) {
    pinMode(rows[r], INPUT);
  }
  for (int c = 0; c < sizeof(cols) / sizeof(int); c++) {
    pinMode(cols[c], OUTPUT);
  }
  Serial.begin(9600);
  Keyboard.begin();
}

char keys[] = {
  '`',  '1',  '2',  '3',  '4',  '5',  '6', '7', '8', '9', '0', '-', '=',  0xB2, // BS
  0xB3, 'Q',  'w',  'e',  'r',  't',  'y', 'u', 'i', 'O', 'p', '[', ']',  0xB0,  // TAB, RETURN
  0xC1, 'A',  's',  'd',  'f',  'g',  'h', 'j', 'k', 'l', ';', "'", "#",  0x0,  // CAPS
  0x81, "|",  'z',  'x',  'c',  'v',  'b', 'n', 'm', ',', '.', '/', 0x85, 0x0,// L/R SHIFT
  0x80, 0x83, 0x82, 0x20, 0x86, 0x87, 0x84
};
// Bitmask`

uint64_t prev_mask = 0x0, curr_mask = 0x0;


void loop() {
  // put your main code here, to run repeatedly:
  for (int c = 0; c < 14; c++) {
    digitalWrite(cols[c], HIGH);

    //
    for (int r = 0; r < 5; r++) {
      int ar = analogRead(rows[r]);
      if (ar > 0) {
        Serial.print(ar);
        Serial.print("\n");
      }
      if (ar > THRESHOLD_UP) {
        Serial.print("Row ");
        Serial.print(r);
        Serial.print(" Column ");
        Serial.print(c);
        Serial.print(" pressed");
        curr_mask |= (uint64_t)((uint64_t)0x1 << ((r * 14) + c));
      }

    }
    digitalWrite(cols[c], LOW);

  }
  // Find which keys to press

  uint64_t new_mask = (~prev_mask) & curr_mask;
  uint64_t old_mask = prev_mask & (~curr_mask);


  for (int i = 0; i < 64; i++) {
    // bit shift mask and compare with 1_16

    if ((old_mask >> i) &  (unsigned int)0x1) {
      Keyboard.release(keys[i]);
      Serial.print("Releasing");
      Serial.print(i);
      Serial.print("\n");
    }
  }
  for (int i = 0; i < 64; i++) {
    if (new_mask >> i & 0x1) {
      Keyboard.press(keys[i]);
      Serial.print("Pressing");
      Serial.print(i);
      Serial.print("\n");
    }
  }
  //
  //
  //


  prev_mask = curr_mask;
  curr_mask = 0x0;
}
//
