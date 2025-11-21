#define GRID_SIZE 4

bool player1Turn = true;

bool player1Ships[GRID_SIZE][GRID_SIZE] = {
  {false, false, true, true},
  {true, false, false, false},
  {true, false, true, false},
  {true, false, true, false}
};

bool player2Ships[GRID_SIZE][GRID_SIZE] = {
  {false, false, true, true},
  {true, false, false, false},
  {true, false, true, false},
  {true, false, true, false}
};

bool player1Hits[GRID_SIZE][GRID_SIZE] = {
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false}
};

bool player2Hits[GRID_SIZE][GRID_SIZE] = {
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false},
  {false, false, false, false}
};

int* getInputCoordinates(String _player, bool (*_hits)[GRID_SIZE][GRID_SIZE], int _coordinates[2]);
void hit(bool (*_grid)[GRID_SIZE][GRID_SIZE], int _x, int _y);
bool hasLost(bool (*_hits)[GRID_SIZE][GRID_SIZE], bool (*_ships)[GRID_SIZE][GRID_SIZE]);
void renderBoards();
int strSplit(String _str, String _delimiter, String* buffer);

void playGame()
{
  bool gameOver = false;
  String player = "";
  
  while (!gameOver)
  {
    renderBoards();

    if (player1Turn) player = "Spiller 1";
    else player = "Spiller 2";

    bool (*targetHits)[GRID_SIZE][GRID_SIZE];

    if (player1Turn) targetHits = &player2Hits;
    else targetHits = &player1Hits;

    bool (*targetShips)[GRID_SIZE][GRID_SIZE];
    if (player1Turn) targetShips = &player2Ships;
    else targetShips = &player2Ships;
    
    int coordinates[2];
    getInputCoordinates(player, targetHits, coordinates);
    
    int x = coordinates[0];
    int y = coordinates[1];

    hit(targetHits, x, y);

    if (targetShips[y][x])
    {
      Serial.println("Træffer!");
    }
    else
    {
      Serial.println("Forbier!");
      player1Turn = !player1Turn;
    }

    gameOver = hasLost(targetHits, targetShips);
  }

  Serial.print(player);
  Serial.println(" har vundet!");
}

int* getInputCoordinates(String _player, bool (*_hits)[GRID_SIZE][GRID_SIZE], int _coordinates[2])
{
  bool inputIsValid = false;
  int x = 0;
  int y = 0;
      
  while (!inputIsValid)
  {
    Serial.print(_player + " indtast koordinater (x, y): ");
    String errorString = "input skal angives som: x, y";

    char* serialInput = Serial.readBytesUntil('\n');
    char* input;
    serialInput.toCharArray(input, serialInput.length());

    char* splitInput[2];
    int splitCount = 0;

    char* token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i <= 2)
    {
      if (i < 2)
      {
        splitInput[i] = token;
        token = strtok(NULL, ",");
      }
      i++;
    }

    Serial.println(splitInput[0]);
    // Serial.println(splitInput[1]);

    if (splitCount == 2)
    {
      inputIsValid = true;
    }
    
    if (inputIsValid)
    {
      x = atoi(splitInput[0]);	
      y = atoi(splitInput[1]);

      if (x < 0 || GRID_SIZE <= x ||
       y < 0 || GRID_SIZE <= y)
      {
        inputIsValid = false;
        errorString = "koordinater skal være hele tal mellem 1 og " + String(GRID_SIZE) + " x: " + String(x) + " y: " + String(y);
      }
    }

    if (inputIsValid)
    {
      if (_hits[y][x])
      {
        inputIsValid = false;
        errorString = "koordinat allerede ramt." + String(" x: " + String(x) + " y: " + String(y));
      }
    }
    
    if (!inputIsValid)
    {
      Serial.println("Ugyldigt input: " + errorString);
    }

    if (inputIsValid)
    {
      Serial.println("Bekræft affyring mod koordinater: (" + String(x+1) + ", " + String(y+1) + ")? (Y/N) ");
      
      char* answer;
      Serial.readBytes(answer, 1);
      
      while (
        *answer != 'Y' &&
        *answer != 'N' &&
        *answer != 'y' &&
        *answer != 'n')
      {
        Serial.readBytes(answer, 1);
      }

      if (*answer = 'N')
      {
        inputIsValid = false;
      }
    }
  }

  _coordinates[0] = x;
  _coordinates[1] = y;
}

void hit(bool _grid[GRID_SIZE][GRID_SIZE], int _x, int _y)
{
  _grid[_y][_x] = true;
}

bool hasLost(bool (*_hits)[GRID_SIZE][GRID_SIZE], bool (*_ships)[GRID_SIZE][GRID_SIZE])
{
  for (int i = 0; i < GRID_SIZE; i++)
  {
    for (int j = 0; j < GRID_SIZE; j++)
    {
      if (_ships[i][j] && !_hits[i][j]) return false;
    }
  }
  return true;
}

void renderBoards()
{
  String lines[GRID_SIZE + 2];
  String player1Board[GRID_SIZE][GRID_SIZE];
  String player2Board[GRID_SIZE][GRID_SIZE];

  if (player1Turn)
  {
    for (int i = 0; i < GRID_SIZE; i++)
    {
      for (int j = 0; j < GRID_SIZE; j++)
      {
        if (player2Hits[i][j] == false &&
          player2Ships[i][j] == false)
        {
          player1Board[i][j] = ".";
          player2Board[i][j] = ".";
        }
        else if (
          player2Hits[i][j] == true &&
          player2Ships[i][j] == false)
        {
          player1Board[i][j] = "X";
          player2Board[i][j] = "X";
        }
        else if (
          player2Hits[i][j] == false &&
          player2Ships[i][j] == true)
        {
          player1Board[i][j] = ".";
          player2Board[i][j] = "#";
        }
        else if (
          player2Hits[i][j] == true &&
          player2Ships[i][j] == true)
        {
          player1Board[i][j] = "O";
          player2Board[i][j] = "O";
        }
      }
    }
  }
  else
  {
    for (int i = 0; i < GRID_SIZE; i++)
    {
      for (int j = 0; j < GRID_SIZE; j++)
      {
        if (player1Hits[i][j] == false &&
          player1Ships[i][j] == false)
        {
          player2Board[i][j] = ".";
          player1Board[i][j] = ".";
        }
        else if (
          player1Hits[i][j] == true &&
          player1Ships[i][j] == false)
        {
          player2Board[i][j] = "X";
          player1Board[i][j] = "X";
        }
        else if (
          player1Hits[i][j] == false &&
          player1Ships[i][j] == true)
        {
          player2Board[i][j] = ".";
          player1Board[i][j] = "#";
        }
        else if (
          player1Hits[i][j] == true &&
          player1Ships[i][j] == true)
        {
          player2Board[i][j] = "O";
          player1Board[i][j] = "O";
        }
      }
    }
  }

  lines[0] = " ";
  for (int i = 0; i < GRID_SIZE; i++)
  {
    lines[0] += "-";
  }
  
  lines[0] += "   ";
  for (int i = 0; i < GRID_SIZE; i++)
  {
    lines[0] += "-";
  }

  for (int i = 1; i < GRID_SIZE+1; i++)
  {
    lines[i] = "|";

    for (int j = 0; j < GRID_SIZE; j++)
    {
      lines[i] += player1Board[i-1][j]; 
    }

    lines[i] += "| |"; 
    for (int j = 0; j < GRID_SIZE; j++)
    {
      lines[i] += player2Board[i-1][j];
    }

    lines[i] += "|";
  }

  lines[GRID_SIZE+1] = " ";
  for (int i = 0; i < GRID_SIZE; i++)
  {
    lines[GRID_SIZE+1] += "-";
  }
  
  lines[GRID_SIZE+1] += "   ";
  for (int i = 0; i < GRID_SIZE; i++)
  {
    lines[GRID_SIZE+1] += "-";
  }

  String result = lines[0] + "\n";
  for (int i = 1; i < GRID_SIZE+2; i++)
  {
    result.concat(lines[i] + "\n");
  }

  Serial.println(result);
}

int strSplit(char* _str, String _delimiter, String** buffer)
{
  
  // --------- dogshit ---------
  // int strLen = _str.length();
  // int delimiterLen = _delimiter.length();
  // int count = 0;
  
  // int i = 0;
  // bool done = false;
  // while (!done && i < strLen)
  // {
  //   int index = _str.indexOf(_delimiter, i);

  //   if (index != -1)
  //   {
  //     i = index + delimiterLen;
  //     count++;
  //   }
  //   else
  //   {
  //     done = true;
  //   }
  // }

  // *buffer = new String[count+1];

  // i = 0;
  // int j = 0;
  // done = false;
  // while (!done && i < strLen)
  // {
  //   int index = _str.indexOf(_delimiter, i);

  //   if (index != -1)
  //   {
  //     Serial.println(i);
  //     Serial.println(index);
  //     Serial.println(j);
  //     *buffer[j] = _str.substring(i, index);
  //     i = index + delimiterLen;
  //     Serial.println(*buffer[j]);
  //     j++;
  //   }
  //   else
  //   {
  //     Serial.println(i);
  //     Serial.println(index);
  //     Serial.println(j);
  //     *buffer[j] = _str.substring(i);
  //     Serial.println(*buffer[j]);
  //     done = true;
  //   }
  // }

  // return count+1;
}