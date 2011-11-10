#ifndef __LEVEL_H
#define __LEVEL_H

#include <vector>

class Level {
    private:
        std::vector<std::vector<int> > m_map;
        int m_mapWidth, m_mapHeight;

    public:
        Level(char *fn);

        void outputMap();

        int getTileAt(int x, int y);
        int getMapWidth();
        int getMapHeight();
};

#endif
