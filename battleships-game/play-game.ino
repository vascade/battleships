bool player1Turn = true;

bool player1Ships[mapSize][mapSize];
bool player2Ships[mapSize][mapSize];
bool player1Hits[mapSize][mapSize];
bool player2Hits[mapSize][mapSize];

int* getInputCoordinates(String _player, bool (*_hits)[mapSize][mapSize], int _coordinates[2]);
void hit(bool (*_grid)[mapSize][mapSize], int _x, int _y);
bool hasLost(bool (*_hits)[mapSize][mapSize], bool (*_ships)[mapSize][mapSize]);
void renderBoards();

void playGame()
{
  bool gameOver = false;
  String player = "";

  generateMap(player1Ships);
  generateMap(player2Ships);
  
  while (!gameOver)
  {
    renderBoards();

    if (player1Turn) player = "Spiller 1";
    else player = "Spiller 2";

    bool (*targetHits)[mapSize][mapSize];

    if (player1Turn) targetHits = &player2Hits;
    else targetHits = &player1Hits;

    bool (*targetShips)[mapSize][mapSize];
    if (player1Turn) targetShips = &player2Ships;
    else targetShips = &player1Ships;

    int coordinates[2];
    if (player1Turn) getInputCoordinates(player, player1Keypad, targetHits, coordinates);
    else getInputCoordinates(player, player2Keypad, targetHits, coordinates);
    
    int x = coordinates[0];
    int y = coordinates[1];

    for (int i = 0; i < 4; i++)
    {
      renderBoards();
      delay(500);
      setLEDXY(x, y, selectColor, 0);
      setLEDXY(x, y, selectColor, 256);
      LEDMatrixes.show();
      delay(500);
    }

    (*targetHits)[y][x] = true;

    if ((*targetShips)[y][x])
    {
      Serial.println("Træffer!");
      renderBoards();
      delay(2000);
    }
    else
    {
      Serial.println("Forbier!");
      renderBoards();
      delay(2000);
      player1Turn = !player1Turn;
    }

    gameOver = hasLost(targetHits, targetShips);
  }
  
  renderBoards();

  Serial.print(player);
  Serial.println(" har vundet!");

  clearAnimation();

  for (int i = 0; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      player1Hits[i][j] = false;
      player2Hits[i][j] = false;
    }
  }
}

int* getInputCoordinates(String _player, Keypad _playerKeypad, bool (*_hits)[mapSize][mapSize], int _coordinates[2])
{
  bool coordinatesConfirmed = false;
  int x = 0;
  int y = 0;
  char key;
  char input[4];

  while (!coordinatesConfirmed)
  {
    Serial.print(_player + " indtast koordinater (x, y): ");
    
    int numbersPressed = 0;
    while (numbersPressed < 4)
    {
      key = _playerKeypad.waitForKey();

      if (key == 'D' && 0 < numbersPressed)
      {
        numbersPressed--;
      }

      if (key < '0' || '9' < key) continue;

      if (numbersPressed != 0 && numbersPressed != 2)
      {
        input[numbersPressed] = key;
        Serial.print(key);
        numbersPressed++;
      }
      else if (key == '0' || key == '1')
      {
        input[numbersPressed] = key;
        Serial.print(key);
        numbersPressed++;
      }

    }

    x = ((input[0] - '0') * 10) + (input[1] - '0')-1;
    y = ((input[2] - '0') * 10) + (input[3] - '0')-1;

    if ((*_hits)[y][x])
    {
      Serial.println("\nMål allerede ramt.");
    }
    else
    {
      Serial.println("\nBekræft mål? (" + String(x+1) + ", " + String(y+1) + ")");
      setLEDXY(x, y, selectColor, 0);
      setLEDXY(x, y, selectColor, 256);
      LEDMatrixes.show();

      bool answer = false;
      while(!answer)
      {
        key = _playerKeypad.getKey();

        if (key == 'C')
        {
          answer = true;
          coordinatesConfirmed = true;
        }
        else if (key == 'D')
        {
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