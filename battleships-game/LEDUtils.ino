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
  ledStrip->show();
  Serial.println(x);
}
