#include <string>
void generateMap(int ships[], bool map[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            map[i][j] = false;
        }
    }


}

int main() {
    std::string mapString = "";
    bool myMap[8][8];
    int ships[] = {1, 2, 3};

    generateMap(ships, myMap);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (myMap[i][j]) {
                mapString += "X";
            }
            else {
                mapString += ".";
            }
        }
        mapString += "\n";
    }
}
