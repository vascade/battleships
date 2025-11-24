#define KP_ROWS 4
#define KP_COLS 4

char keyLayout[KP_ROWS][KP_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte player1KPRowPins[KP_ROWS] = {37, 35, 33, 31};
byte player1KPColPins[KP_COLS] = {29, 27, 25, 23};

byte player2KPRowPins[KP_ROWS] = {53, 51, 49, 47};
byte player2KPColPins[KP_COLS] = {45, 43, 41, 39};

Keypad player1Keypad = Keypad(makeKeymap(keyLayout), player1KPRowPins, player1KPColPins, KP_ROWS, KP_COLS);
Keypad player2Keypad = Keypad(makeKeymap(keyLayout), player2KPRowPins, player2KPColPins, KP_ROWS, KP_COLS);