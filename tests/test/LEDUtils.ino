void setLEDXY(Adafruit_NeoPixel ledStrip, int x, int y, uint32_t color)
{
  ledStrip.setPixelColor(x + y*8, color);
  ledStrip.show();
  Serial.println(x);
}
