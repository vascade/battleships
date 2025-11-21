#include <Keypad.h>

#define KP_ROWS 4
#define KP_COLS 4

char keyLayout[KP_ROWS][KP_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte player1KPRowPins[KP_ROWS] = {9, 8, 7, 6};
byte player1KPColPins[KP_COLS] = {5, 4, 3, 2};

byte player2KPRowPins[KP_ROWS] = {9, 8, 7, 6};
byte player2KPColPins[KP_COLS] = {5, 4, 3, 2};

Keypad player1Keypad = Keypad(makeKeymap(keyLayout), player1KPRowPins, player1KPColPins, KP_ROWS, KP_COLS);
Keypad player2Keypad = Keypad(makeKeymap(keyLayout), player2KPRowPins, player2KPColPins, KP_ROWS, KP_COLS);