uint32_t noColor = LEDMatrixes.Color(0, 0, 0);
uint32_t shipColor = LEDMatrixes.Color(0, 0, 10);
uint32_t ownHitColor = LEDMatrixes.Color(10, 0, 0);
uint32_t ownMissColor = LEDMatrixes.Color(0, 10, 0);
uint32_t oppHitColor = LEDMatrixes.Color(0, 10, 0);
uint32_t oppMissColor = LEDMatrixes.Color(10, 0, 0);

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
    
    // int coordinates[2];
    // getInputCoordinates(player, targetHits, coordinates);
    
    // int x = coordinates[0];
    // int y = coordinates[1];

    // hit(targetHits, x, y);

    // if (targetShips[y][x])
    // {
    //   Serial.println("Træffer!");
    // }
    // else
    // {
    //   Serial.println("Forbier!");
    //   player1Turn = !player1Turn;
    // }

    delay(1000);
    player1Turn = !player1Turn;

    // gameOver = hasLost(targetHits, targetShips);
  }

  Serial.print(player);
  Serial.println(" har vundet!");
}

// int* getInputCoordinates(String _player, bool (*_hits)[mapSize][mapSize], int _coordinates[2])
// {
//   bool inputIsValid = false;
//   int x = 0;
//   int y = 0;
      
//   while (!inputIsValid)
//   {
//     Serial.print(_player + " indtast koordinater (x, y): ");
//     String errorString = "input skal angives som: x, y";

//     char* serialInput = Serial.readBytesUntil('\n');
//     char* input;
//     serialInput.toCharArray(input, serialInput.length());

//     char* splitInput[2];
//     int splitCount = 0;

//     char* token = strtok(input, ",");
//     int i = 0;
//     while (token != NULL && i <= 2)
//     {
//       if (i < 2)
//       {
//         splitInput[i] = token;
//         token = strtok(NULL, ",");
//       }
//       i++;
//     }

//     Serial.println(splitInput[0]);
//     // Serial.println(splitInput[1]);

//     if (splitCount == 2)
//     {
//       inputIsValid = true;
//     }
    
//     if (inputIsValid)
//     {
//       x = atoi(splitInput[0]);	
//       y = atoi(splitInput[1]);

//       if (x < 0 || mapSize <= x ||
//        y < 0 || mapSize <= y)
//       {
//         inputIsValid = false;
//         errorString = "koordinater skal være hele tal mellem 1 og " + String(mapSize) + " x: " + String(x) + " y: " + String(y);
//       }
//     }

//     if (inputIsValid)
//     {
//       if (_hits[y][x])
//       {
//         inputIsValid = false;
//         errorString = "koordinat allerede ramt." + String(" x: " + String(x) + " y: " + String(y));
//       }
//     }
    
//     if (!inputIsValid)
//     {
//       Serial.println("Ugyldigt input: " + errorString);
//     }

//     if (inputIsValid)
//     {
//       Serial.println("Bekræft affyring mod koordinater: (" + String(x+1) + ", " + String(y+1) + ")? (Y/N) ");
      
//       char* answer;
//       Serial.readBytes(answer, 1);
      
//       while (
//         *answer != 'Y' &&
//         *answer != 'N' &&
//         *answer != 'y' &&
//         *answer != 'n')
//       {
//         Serial.readBytes(answer, 1);
//       }

//       if (*answer = 'N')
//       {
//         inputIsValid = false;
//       }
//     }
//   }

//   _coordinates[0] = x;
//   _coordinates[1] = y;
// }

void hit(bool _grid[mapSize][mapSize], int _x, int _y)
{
  _grid[_y][_x] = true;
}

bool hasLost(bool (*_hits)[mapSize][mapSize], bool (*_ships)[mapSize][mapSize])
{
  for (int i = 0; i < mapSize; i++)
  {
    for (int j = 0; j < mapSize; j++)
    {
      if (_ships[i][j] && !_hits[i][j]) return false;
    }
  }
  return true;
}

void renderBoards()
{
  Serial.println("Rendering...");
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

  drawMap(&LEDMatrixes, player1Board, 0);
  drawMap(&LEDMatrixes, player2Board, 256);

  LEDMatrixes.show();
}