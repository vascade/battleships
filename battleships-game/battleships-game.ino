#include <Adafruit_NeoPixel.h>

const int mapSize = 16;
const int randPin = 0;
Adafruit_NeoPixel matrix(512, 2, NEO_GRB + NEO_KHZ800);

void setup() {
    matrix.begin();

    matrix.clear();
    // Start her
    int myMap1[mapSize][mapSize];
    int myMap2[mapSize][mapSize];

    generateMap(myMap1);
    generateMap(myMap2);
    // Bom, nu har du et tilfældigt map.

    for (int i = 0; i < mapSize; i++) {
      for (int j = 0; j < mapSize; j++) {
          if (myMap1[i][j] == 2) {
              setLEDXY(&matrix, j, i, matrix.Color(30, 0, 30), 0);
          }
          if (myMap2[i][j] == 2) {
              setLEDXY(&matrix, j, i, matrix.Color(30, 0, 30), 256);
          }
      }

  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
