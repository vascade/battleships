#include <Keypad.h>

#define KP_ROWS 4
#define KP_COLS 4

char keyLayout[KP_ROWS][KP_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte keypadRowPins[KP_ROWS] = {9, 8, 7, 6};
byte keypadColPins[KP_COLS] = {5, 4, 3, 2};

Keypad kp = Keypad(makeKeymap(keyLayout), keypadRowPins, keypadColPins, KP_ROWS, KP_COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = kp.getKey();

  if (key) Serial.println(key);
}
