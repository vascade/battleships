bool player1Turn = true;

bool player1Ships[mapSize][mapSize];
bool player2Ships[mapSize][mapSize];
bool player1Hits[mapSize][mapSize];
bool player2Hits[mapSize][mapSize];

Keypad* currentPlayerKeypad;
LiquidCrystal* currentPlayerLCD;
String currentPlayer = "";

void getInputCoordinates(bool (*_hits)[mapSize][mapSize], int _coordinates[2]);
void hit(bool (*_grid)[mapSize][mapSize], int _x, int _y);
bool hasLost(bool (*_hits)[mapSize][mapSize], bool (*_ships)[mapSize][mapSize]);
void renderBoards();

void playGame()
{
  bool gameOver = false;

  generateMap(player1Ships);
  generateMap(player2Ships);

  while (!gameOver)
  {
    renderBoards();

    bool (*targetHits)[mapSize][mapSize];
    bool (*targetShips)[mapSize][mapSize];

    int coordinates[2];
    if (player1Turn)
    {
      currentPlayer = "Spiller 1";
      currentPlayerKeypad = &player1Keypad;
      currentPlayerLCD = &player1LCD;
      targetHits = &player2Hits;
      targetShips = &player2Ships;
      LCDClearPrint(player2LCD, "Modstanders tur");
      getInputCoordinates(targetHits, coordinates);
    }
    else
    {
      currentPlayer = "Spiller 2";
      currentPlayerKeypad = &player2Keypad;
      currentPlayerLCD = &player2LCD;
      targetHits = &player1Hits;
      targetShips = &player1Ships;
      LCDClearPrint(player1LCD, "Modstanders tur");
      getInputCoordinates(targetHits, coordinates);
    }

    int x = coordinates[0];
    int y = coordinates[1];

    LCDClearPrint(player1LCD, "Affyrer...");
    LCDClearPrint(player2LCD, "Affyrer...");
    // setSong(Alarm, ALARM_LENGTH);

    for (int i = 0; i < 3; i++)
    {
      renderBoards();
      
      playAlarm();

      setLEDXY(x, y, selectColor, 0);
      setLEDXY(x, y, selectColor, 256);
      LEDMatrixes.show();
      
      playAlarm();
    }

    (*targetHits)[y][x] = true;

    if ((*targetShips)[y][x])
    {
      LCDClearPrint(player1LCD, "Pletskud!");
      LCDClearPrint(player2LCD, "Pletskud!");
      renderBoards();
      playHit();
      delay(1000);
    }
    else
    {
      LCDClearPrint(player1LCD, "Forbier!");
      LCDClearPrint(player2LCD, "Forbier!");
      renderBoards();
      playMiss();
      delay(1800);
      player1Turn = !player1Turn;
    }

    gameOver = hasLost(targetHits, targetShips);
  }

  renderBoards();

  LCDClearPrint(player1LCD, currentPlayer + " har vundet!");
  LCDClearPrint(player2LCD, currentPlayer + " har vundet!");

  clearAnimation();
  
  setSong(seaShanty2, SEASHANTY2_LENGTH);

  for (int i = 0; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      player1Hits[i][j] = false;
      player2Hits[i][j] = false;
    }
  }
}

void getInputCoordinates(bool (*_hits)[mapSize][mapSize], int _coordinates[2])
{
  bool coordinatesConfirmed = false;
  int x = 0;
  int y = 0;
  char key;
  char input[4];

  while (!coordinatesConfirmed)
  {
    LCDClearPrint(*currentPlayerLCD, "Tast koordinater");
    currentPlayerLCD->setCursor(0, 1);
    currentPlayerLCD->print("01-16: X:   Y:  ");
    currentPlayerLCD->setCursor(9, 1);
    currentPlayerLCD->blink();
    
    int numbersPressed = 0;
    while (numbersPressed < 4)
    {
      key = currentPlayerKeypad->waitForKey();

      if (key == 'D' && 0 < numbersPressed)
      {
        numbersPressed--;
        tonePlayer.play(DELETE_TONE, 100);
        if (numbersPressed < 2)
        {
          currentPlayerLCD->setCursor(9 + numbersPressed, 1);
        }
        else
        {
          currentPlayerLCD->setCursor(14 + numbersPressed - 2, 1);
        }

        currentPlayerLCD->write(' ');

        if (numbersPressed < 2)
        {
          currentPlayerLCD->setCursor(9 + numbersPressed, 1);
        }
        else
        {
          currentPlayerLCD->setCursor(14 + numbersPressed - 2, 1);
        }
      }

      if (key < '0' || '9' < key) continue;

      if (
        (numbersPressed == 0 || numbersPressed == 2) &&
        (key != '0' && key != '1'))
      {
        continue;
      }
      
      if (
        (numbersPressed == 1 && input[0] == '0' && key == '0') ||
        (numbersPressed == 3 && input[2] == '0' && key == '0'))
      {
        continue;
      }

      input[numbersPressed] = key;
      currentPlayerLCD->print(key);
      numbersPressed++;
      tonePlayer.play(BUZZ_TONE, 100);

      if (numbersPressed == 2)
      {
        currentPlayerLCD->setCursor(14, 1);
      }
    }

    x = ((input[0] - '0') * 10) + (input[1] - '0')-1;
    y = ((input[2] - '0') * 10) + (input[3] - '0')-1;

    if ((*_hits)[y][x])
    {
      LCDClearPrint(*currentPlayerLCD, "Koordinat");
      currentPlayerLCD->setCursor(0, 1);
      currentPlayerLCD->print("allerede ramt.");
      tonePlayer.play(ERROR_TONE, 100);
      delay(150);
      tonePlayer.play(ERROR_TONE, 200);
      delay(2000);
    }
    else
    {
      LCDClearPrint(*currentPlayerLCD, "Er du sikker?");
      currentPlayerLCD->setCursor(0, 1);
      currentPlayerLCD->print("(" + String(x+1) + ", " + String(y+1) + ")");
      setLEDXY(x, y, selectColor, 0);
      setLEDXY(x, y, selectColor, 256);
      LEDMatrixes.show();

      bool answer = false;
      while(!answer)
      {
        key = currentPlayerKeypad->getKey();

        if (key == 'C')
        {
          tonePlayer.play(BUZZ_TONE, 100);
          answer = true;
          coordinatesConfirmed = true;
        }
        else if (key == 'D')
        {
          tonePlayer.play(DELETE_TONE, 100);
          answer = true;
        }
      }
    }

    setLEDXY(x, y, noColor, 0);
    setLEDXY(x, y, noColor, 256);
    renderBoards();
  }

  _coordinates[0] = x;
  _coordinates[1] = y;
}

bool hasLost(bool (*_hits)[mapSize][mapSize], bool (*_ships)[mapSize][mapSize])
{
  for (int i = 0; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      if ((*_ships)[i][j] && !(*_hits)[i][j]) return false;
    }
  }
  return true;
}

void renderBoards()
{
  uint32_t player1Board[mapSize][mapSize];
  uint32_t player2Board[mapSize][mapSize];

  if (player1Turn)
  {
    for (int i = 0; i < mapSize; i++)
    {
      for (int j = 0; j < mapSize; j++)
      {
        if (player2Hits[i][j] == false &&
          player2Ships[i][j] == false)
        {
          player1Board[i][j] = noColor;
          player2Board[i][j] = noColor;
        }
        else if (
          player2Hits[i][j] == true &&
          player2Ships[i][j] == false)
        {
          player1Board[i][j] = oppMissColor;
          player2Board[i][j] = ownMissColor;
        }
        else if (
          player2Hits[i][j] == false &&
          player2Ships[i][j] == true)
        {
          player1Board[i][j] = noColor;
          player2Board[i][j] = shipColor;
        }
        else if (
          player2Hits[i][j] == true &&
          player2Ships[i][j] == true)
        {
          player1Board[i][j] = oppHitColor;
          player2Board[i][j] = ownHitColor;
        }
      }
    }
  }
  else
  {
    for (int i = 0; i < mapSize; i++)
    {
      for (int j = 0; j < mapSize; j++)
      {
        if (player1Hits[i][j] == false &&
          player1Ships[i][j] == false)
        {
          player2Board[i][j] = noColor;
          player1Board[i][j] = noColor;
        }
        else if (
          player1Hits[i][j] == true &&
          player1Ships[i][j] == false)
        {
          player2Board[i][j] = oppMissColor;
          player1Board[i][j] = ownMissColor;
        }
        else if (
          player1Hits[i][j] == false &&
          player1Ships[i][j] == true)
        {
          player2Board[i][j] = noColor;
          player1Board[i][j] = shipColor;
        }
        else if (
          player1Hits[i][j] == true &&
          player1Ships[i][j] == true)
        {
          player2Board[i][j] = oppHitColor;
          player1Board[i][j] = ownHitColor;
        }
      }
    }
  }

  LEDMatrixes.clear();

  drawMap(player1Board, 0);
  drawMap(player2Board, 256);

  LEDMatrixes.show();
}

void renderShips()
{
  uint32_t player1Board[mapSize][mapSize];
  uint32_t player2Board[mapSize][mapSize];

  for (int i = 0; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      if (player1Ships[i][j] == true) player1Board[i][j] = true;
      if (player2Ships[i][j] == true) player2Board[i][j] = true;
    }
  }

  LEDMatrixes.clear();

  drawMap(player1Board, 0);
  drawMap(player2Board, 256);

  LEDMatrixes.show();
}