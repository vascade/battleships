#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

Adafruit_NeoPixel LEDMatrixes(512, 2, NEO_GRB + NEO_KHZ800);

const uint32_t noColor = LEDMatrixes.Color(0, 0, 0);
const uint32_t shipColor = LEDMatrixes.Color(0, 0, 5);
const uint32_t ownHitColor = LEDMatrixes.Color(5, 0, 0);
const uint32_t ownMissColor = LEDMatrixes.Color(0, 5, 0);
const uint32_t oppHitColor = LEDMatrixes.Color(0, 5, 0);
const uint32_t oppMissColor = LEDMatrixes.Color(5, 0, 0);
const uint32_t selectColor = LEDMatrixes.Color(5, 2, 0);

const int mapSize = 16;
const int randPin = 0;

void setup() {
  LEDMatrixes.begin();

  LEDMatrixes.clear();

  Serial.begin(9600);
//   // Start her
//   int myMap1[mapSize][mapSize];
//   int myMap2[mapSize][mapSize];

//   generateMap(myMap1);
//   generateMap(myMap2);
//   // Bom, nu har du et tilfældigt map.

//   for (int i = 0; i < mapSize; i++) {
//     for (int j = 0; j < mapSize; j++) {
//         if (myMap1[i][j] == 2) {
//             setLEDXY(&matrix, j, i, matrix.Color(30, 0, 30), 0);
//         }
//         if (myMap2[i][j] == 2) {
//             setLEDXY(&matrix, j, i, matrix.Color(30, 0, 30), 256);
//         }
//     }

// }
}

void loop() {
  // put your main code here, to run repeatedly:
  playGame();
  // setLEDXY(&LEDMatrixes, 2, 2, LEDMatrixes.Color(10, 10, 10), 0);
}