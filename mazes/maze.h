#ifndef MAZE_H
#define MAZE_H

#include "mazeNode.h"
class maze {
    public:
        Maze(int width, int height);
        ~Maze();
        bool allVisited();
        bool visit(int x, int y);
        bool visit(MazeNode* node);
        bool removeWall(int x, int y, Direction dir);
        bool removeWall(int x1, int y1, int x2, int y2);
        MazeNode* getNode(int x, int y);

    private:
        MazeNode** maze;
        int w;
        int h;

}

#endif
