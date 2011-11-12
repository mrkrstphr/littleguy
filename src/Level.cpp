#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Level.h"

Level::Level(char *fn) : m_mapWidth(-1), m_mapHeight(-1) {
    std::string line;
    std::ifstream myfile(fn);

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            getline(myfile, line);
            if (line == "") break;

            std::vector<int> row;

            if (line.substr(0, 2) == "{{")
                line = line.substr(2, line.length() - 2);
            if (line.substr(line.length() - 3, 2) == "}}")
               line = line.substr(0, line.length() - 3);
            if (line.substr(line.length() - 3, 2) == "},")
               line = line.substr(0, line.length() - 3);
            if (line.substr(0, 2) == " {")
               line = line.substr(2, line.length() - 2);

            int f = line.find(",");
            while ((f = line.find(",")) != std::string::npos) {
                int e = atoi(line.substr(0, f).c_str());

                row.push_back(e);
                line = line.substr(f + 1);
            }
            
            int e = atoi(line.substr(0, f).c_str());
            row.push_back(e);

            if (m_mapWidth == -1) {
                m_mapWidth = row.size();
            } else if (m_mapWidth != row.size()) {
                //throw Exception("Inconsistent map width");
                printf("Inconsistent map width\n");
            }
            
            m_map.push_back(row);
        }

        m_mapHeight = m_map.size();

        myfile.close();
    }
}

void Level::outputMap() {
    for (int y = 0; y < m_mapHeight; y++) {
        for (int x = 0; x < m_mapWidth; x++) {
            printf("%d ", getTileAt(x, y));
        }
        printf("\n");
    }
}

int Level::getTileAt(int x, int y) {
    return m_map.at(y).at(x);
}

int Level::getMapWidth() {
    return m_mapWidth;
}

int Level::getMapHeight() {
    return m_mapHeight;
}
