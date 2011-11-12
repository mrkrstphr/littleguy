#ifndef __LEVEL_H
#define __LEVEL_H

#include <vector>

class Level {
    private:
        std::vector<std::vector<int> > m_map;
        int m_width, m_height;

    public:
        Level(char *fn);

        void outputMap();

        int getTileAt(int x, int y);
        int getWidth();
        int getHeight();
};

#endif
