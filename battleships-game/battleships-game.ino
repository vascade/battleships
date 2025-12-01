#include <Adafruit_NeoPixel.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Tone.h>
#include <TimerOne.h>

#define SEASHANTY2_LENGTH 53

#define BUZZ_PIN 12
#define BUZZ_TONE NOTE_C5
#define DELETE_TONE NOTE_C4
#define ERROR_TONE NOTE_C3
#define ALARM_START NOTE_C4
#define ALARM_END NOTE_D4

#define mapSize 16
#define randPin 0

#define NUM_OF_LEDS 512
#define LED_PIN 2

#define KP_ROWS 4
#define KP_COLS 4

#define LCD1_RS 22
#define LCD1_EN 24
#define LCD1_D4 26
#define LCD1_D5 28
#define LCD1_D6 30
#define LCD1_D7 32

#define LCD2_RS 34
#define LCD2_EN 36
#define LCD2_D4 38
#define LCD2_D5 40
#define LCD2_D6 42
#define LCD2_D7 44

struct Note
{
  int frequency;
  int duration;
};

struct Song
{
  Note* notes;
  int notesLength;
  int currentNote;
};

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

Adafruit_NeoPixel LEDMatrixes(NUM_OF_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

LiquidCrystal player1LCD(LCD1_RS, LCD1_EN, LCD1_D4, LCD1_D5, LCD1_D6, LCD1_D7);
LiquidCrystal player2LCD(LCD2_RS, LCD2_EN, LCD2_D4, LCD2_D5, LCD2_D6, LCD2_D7);


const uint32_t noColor = LEDMatrixes.Color(0, 0, 0);
const uint32_t shipColor = LEDMatrixes.Color(0, 0, 5);
const uint32_t ownHitColor = LEDMatrixes.Color(5, 0, 0);
const uint32_t ownMissColor = LEDMatrixes.Color(0, 5, 0);
const uint32_t oppHitColor = LEDMatrixes.Color(0, 5, 0);
const uint32_t oppMissColor = LEDMatrixes.Color(5, 0, 0);
const uint32_t selectColor = LEDMatrixes.Color(5, 2, 0);

Note* seaShanty2;
Note* Alarm;

Tone tonePlayer;
Song currentSong;

int bpm = 400; // song tempo in sixteenth notes

void setup() {
  initSongs();
  tonePlayer.begin(BUZZ_PIN);

  player1LCD.begin(16, 2);
  player2LCD.begin(16, 2);

  LEDMatrixes.begin();
  LEDMatrixes.clear();

  Timer1.initialize(60000000/bpm); // timer set to sixteenth notes in µs
  Timer1.attachInterrupt(playSong);
}

void loop() {
  playGame();
}