const int mapSize = 16;
const int randPin = 0;

void setup() {
    Serial.begin(115200);
    String mapString = "";
    // Start her
    int myMap[mapSize][mapSize];
    generateMap(myMap);
    // Bom, nu har du et tilfældigt map.

    for (int i = 0; i < mapSize; i++) {
      for (int j = 0; j < mapSize; j++) {
          if (myMap[i][j] == 2) {
              mapString += "X";
          }
          else {
              mapString += ".";
          }
      }
      mapString += "\n";
  }
  Serial.println(mapString);
}

void loop() {
  // put your main code here, to run repeatedly:

}
