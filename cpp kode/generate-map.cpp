#include <algorithm>
#include <iostream>
#include <string>
#include <random>

const int mapSize = 8;

int random(int min, int max) {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(min, max); // define the range

    return distr(gen);
}

void placeShips(bool map[mapSize][mapSize], int rowStart, int rowEnd, int colStart, int colEnd) {
    for (int i = rowStart; i <= rowEnd; i++) {
        for (int j = colStart; j <= colEnd; j++) {
            map[i][j] = true;
        }
    }
}

bool isAvailAround(bool map[mapSize][mapSize], int rowStart, int rowEnd, int colStart, int colEnd) {

    for (int i = rowStart; i <= rowEnd; i++) {
        for (int j = colStart; j <= colEnd; j++) {
            if (map[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int checkDirection(int x, int y, int shipLength, int direction) {
    if (direction == 0) {
        if (y-shipLength-1 < 0) {
            return false;
        }

        return true;
    }
    else if (direction == 2) {
        if (y+shipLength-1 > mapSize - 1) {
            return false;
        }
        return true;
    }
    else if (direction == 3) {
        if (x-shipLength-1 > 0) {
            return false;
        }
        return true;
    }
    else if (direction == 1) {
        if (x+shipLength-1 > mapSize - 1) {
            return false;
        }
        return true;
    }
}

void generateMap(int ships[], bool map[mapSize][mapSize]) {
    // Fill the map with false
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            map[i][j] = false;
        }
    }

    // for each ship
    for (int i = 0; i < 3; i++) {

        bool availablePos = false;

        while (!availablePos) {
            int startX = random(0, mapSize - 1);
            int startY = random(0, mapSize - 1);

            int range = 1;
            int rowStart = std::max(0, startX-range);
            int rowEnd = std::min(mapSize-1, startX+range);
            int colStart = std::max(0, startY-range);
            int colEnd = std::min(mapSize-1, startY+range);

            // Check if the random position is occupied by another ship.
            if (!isAvailAround(map, rowStart, rowEnd, colStart, colEnd)) {
                continue;
            }

            // Check if ship can fit
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


            // Check around ship

        }
    }
}

int main() {
    std::string mapString = "";
    bool myMap[mapSize][mapSize];
    int ships[] = {3, 2, 1};

    generateMap(ships, myMap);

    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            if (myMap[i][j]) {
                mapString += "X";
            }
            else {
                mapString += ".";
            }
        }
        mapString += "\n";
    }
    std::cout << mapString;
}
