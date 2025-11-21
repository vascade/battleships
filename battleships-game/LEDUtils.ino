void setLEDXY(Adafruit_NeoPixel* ledStrip, int x, int y, uint32_t color)
{
  ledStrip->clear();
  ledStrip->setPixelColor(x + y*16, color);
  ledStrip->show();
  Serial.println(x);
}
