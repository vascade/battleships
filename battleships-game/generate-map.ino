void placeShips(int map[mapSize][mapSize], int rowStart, int rowEnd, int colStart, int colEnd) {
    for (int i = rowStart; i <= rowEnd; i++) {
        for (int j = colStart; j <= colEnd; j++) {
            map[i][j] = 1;
        }
    }
}

bool isAvailAround(int map[mapSize][mapSize], int rowStart, int rowEnd, int colStart, int colEnd) {

    for (int i = rowStart; i <= rowEnd; i++) {
        for (int j = colStart; j <= colEnd; j++) {
            if (map[i][j] == 1) {
                return false;
            }
            else if (map[i][j] == 2) {
                return false;
            }
        }
    }
    return true;
}

bool checkDirection(int x, int y, int shipLength, int direction) {
    switch(direction) {
        case 0: // up
            return x - (shipLength - 1) >= 0;
        case 1: // right
            return y + (shipLength - 1) < mapSize;
        case 2: // down
            return x + (shipLength - 1) < mapSize;
        case 3: // left
            return y - (shipLength - 1) >= 0;
    }
    return false;
}

void generateMap(int map[mapSize][mapSize]) {
    randomSeed(analogRead(randPin));
    int ships[] = {5, 4, 4, 4, 4, 3, 3, 3, 3, 2};

    // Fill the map with false
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            map[i][j] = 0;
        }
    }

    // for each ship
    for (int i = 0; i < 10; i++) {

        bool availablePos = false;

        while (!availablePos) {
            int startX = random(0, mapSize - 1);
            int startY = random(0, mapSize - 1);

            int range = 1;
            int rowStart = max(0, startX-range);
            int rowEnd = min(mapSize-1, startX+range);
            int colStart = max(0, startY-range);
            int colEnd = min(mapSize-1, startY+range);

            // Check if the random position is occupied by another ship.
            if (!isAvailAround(map, rowStart, rowEnd, colStart, colEnd)) {
                continue;
            }

            // Find a random direction for the ship
            int direction = random(0, 3);
            int counter = 0;
            bool foundDirection = false;
            while (counter < 4 && !foundDirection) {
                if (!checkDirection(startX, startY, ships[i], direction)) {
                    counter++;
                    if (direction == 3) {
                        direction = 0;
                    } else {
                        direction++;
                    }
                } else {
                    foundDirection = true;
                }
            }
            if (!foundDirection) {
                continue;
            }

            // Draw everything for "up" direction
            if (direction == 0) {
                for (int u = 0; u < ships[i]; u++) {
                    if (!isAvailAround(map, rowStart-u, rowEnd, colStart, colEnd)) {
                        availablePos = false;
                        goto exitNow;
                    }
                    availablePos = true;
                }
                for (int u = 0; u < ships[i]; u++) {
                    placeShips(map, rowStart-u, rowEnd, colStart, colEnd);
                }
                for (int u = 0; u < ships[i]; u++) {
                    map[startX-u][startY] = 2;
                }
            }
            // Draw everything for "down" direction
            if (direction == 2) {
                for (int u = 0; u < ships[i]; u++) {
                    if (!isAvailAround(map, rowStart, rowEnd+u, colStart, colEnd)) {
                        availablePos = false;
                        goto exitNow;
                    }
                    availablePos = true;
                }
                for (int u = 0; u < ships[i]; u++) {
                    placeShips(map, rowStart, rowEnd+u, colStart, colEnd);
                }
                for (int u = 0; u < ships[i]; u++) {
                    map[startX+u][startY] = 2;
                }
            }
            // Draw everything for "right" direction
            if (direction == 1) {
                for (int u = 0; u < ships[i]; u++) {
                    if (!isAvailAround(map, rowStart, rowEnd, colStart, colEnd+u)) {
                        availablePos = false;
                        goto exitNow;
                    }
                    availablePos = true;
                }
                for (int u = 0; u < ships[i]; u++) {
                    placeShips(map, rowStart, rowEnd, colStart, colEnd+u);
                }
                for (int u = 0; u < ships[i]; u++) {
                    map[startX][startY+u] = 2;
                }
            }
            // Draw everything for "right" direction
            if (direction == 3) {
                for (int u = 0; u < ships[i]; u++) {
                    if (!isAvailAround(map, rowStart, rowEnd, colStart-u, colEnd)) {
                        availablePos = false;
                        goto exitNow;
                    }
                    availablePos = true;
                }
                for (int u = 0; u < ships[i]; u++) {
                    placeShips(map, rowStart, rowEnd, colStart-u, colEnd);
                }
                for (int u = 0; u < ships[i]; u++) {
                    map[startX][startY-u] = 2;
                }
            }
            exitNow:
            continue;
        }
    }
}
