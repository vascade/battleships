void setLEDXY(Adafruit_NeoPixel* ledStrip, int x, int y, uint32_t color, int startIndex)
{
  int index;
  if (y % 2 == 0) {
    index = y * mapSize + (mapSize - 1 - x);
  } 
  else {
    index = y * mapSize + x;
  }

  ledStrip->setPixelColor(index + startIndex, color);
  // ledStrip->show();
}

void drawMap(Adafruit_NeoPixel* ledStrip, uint32_t colorMap[mapSize][mapSize], int startIndex)
{
  Serial.print("Drawing colors: ");
  for (int i = 0; i < mapSize; i++) {
    for (int j = 0; j < mapSize; j++) {
      Serial.println(colorMap[j][i]);
      setLEDXY(ledStrip, j, i, colorMap[j][i], startIndex);
    }
  }
}