void setLEDXY(int x, int y, uint32_t color, int startIndex)
{
  int index;
  if (y % 2 == 0)
  {
    index = y * mapSize + (mapSize - 1 - x);
  } 
  else
  {
    index = y * mapSize + x;
  }

  LEDMatrixes.setPixelColor(index + startIndex, color);
}

void drawMap(uint32_t colorMap[mapSize][mapSize], int startIndex)
{
  for (int i = 0; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      setLEDXY(j, i, colorMap[i][j], startIndex);
    }
  }
}

void clearAnimation()
{
  for (int i = 0; i < mapSize; i++)
  {
    setLEDXY(0, i, shipColor, 0);
    setLEDXY(0, i, shipColor, 256);
    LEDMatrixes.show();
  }

  delay(10);
  
  for (int i = 1; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      setLEDXY(i-1, j, noColor, 0);
      setLEDXY(i-1, j, noColor, 256);
      setLEDXY(i, j, shipColor, 0);
      setLEDXY(i, j, shipColor, 256);
      LEDMatrixes.show();
    }

    delay(10);
  }

  for (int i = 0; i < mapSize; i++)
  {
    setLEDXY(mapSize-1, i, noColor, 0);
    setLEDXY(mapSize-1, i, noColor, 256);
    LEDMatrixes.show();
  }
}