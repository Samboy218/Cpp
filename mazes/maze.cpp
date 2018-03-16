#include "maze.h"

Maze::Maze(int width, int height) {
    w = width;
    h = height;
    maze = (MazeNode**)malloc(sizeof(MazeNode*)*w*h);
    //init all nodes
    for (int i = 0; i < w*h; i++) {
        maze[i] = new MazeNode();
    }
}

Maze::~Maze() {
    for (int i = 0; i < w*h; i++) {
        delete maze[i];
    }
    free(maze)
}

bool Maze::allVisited() {
    for (int i = 0; i < w*h; i++) {
        if (!maze[i].visited())
            return false;
    }
    return true;
}
bool Maze::visit(int x, int y) {
    return visit(getNode(int x, int y));
}

bool Maze::visit(MazeNode* node) {
    if (node == NULL)
        reutrn false;
    node->visit();
}

bool Maze::removeWall(int x, int y, Direction dir) {
    MazeNode* node1 = getNode(x, y);
    MazeNode* node2;
    Direction dir2;
    switch dir {
        case NORTH:
            node2 = getNode(x, y+1);
            dir2 = SOUTH;
            break;
        case NORTH-WEST:
            node2 = getNode(x-1, y+1);
            dir2 = SOUTH-EAST;
            break;
        case NORTH-EAST:
            node2 = getNode(x+1, y+1);
            dir2 = SOUTH-WEST;
            break;
        case SOUTH:
            node2 = getNode(x, y-1);
            dir2 = NORTH;
            break;
        case SOUTH-WEST:
            node2 = getNode(x-1, y-1);
            dir2 = NORTH-EAST;
            break;
        case SOUTH-EAST:
            node2 = getNode(x+1, y-1);
            dir2 = NORTH-WEST;
            break;
        case WEST:
            node2 = getNode(x-1, y);
            dir2 = EAST;
            break;
        case EAST:
            node2 = getNode(x+1, y);
            dir2 = WEST;
            break;
        default:
            node2=NULL
    }
    if (! (node1 && node2))
        return false;

    return (removeWall(node1, dir) && removeWall(node2, dir2))
}


bool Maze::removeWall(int x1, int y1, int x2, int y2) {
    MazeNode* node1 = getNode(x1, y1);
    if (!node1)
        return false;
    MazeNode* node2 = getNode(x2, y2);
    if (!node2)
        return false;
    xdiff = x1 - x2;
    ydiff = y1 - y2;
    if (xdiff > 1 || xdiff < -1 || ydiff > 1 || ydiff < -1 || xdiff == ydiff)
        return false;
    //now get the direction for each node
    Direction dir1;
    Direction dir2;
    if (xdiff == 0 && ydiff == 1) {
        dir1 = NORTH;
        dir2 = SOUTH;
    }
    else if (xdiff == 1 && ydiff == 1) {
        dir1 = NORTH-EAST;
        dir2 = SOUTH-WEST;
    }
    else if (xdiff == -1 && ydiff == 1) {
        dir1 = NORTH-WEST;
        dir2 = SOUTH-EAST;
    }
    else if (xdiff == 0 && ydiff == -1) {
        dir1 = SOUTH;
        dir2 = NORTH;
    }
    else if (xdiff == 1 && ydiff == -1) {
        dir1 = SOUTH-EAST;
        dir2 = NORTH-WEST;
    }
    else if (xdiff == -1 && ydiff == -1) {
        dir1 = SOUTH-WEST;
        dir2 = NORTH-EAST;
    }
    else if (xdiff == 1 && ydiff == 0) {
        dir1 = EAST;
        dir2 = WEST;
    }
    else if (xdiff == -1 && ydiff == 0) {
        dir1 = WEST;
        dir2 = EAST;
    }

    return (removeWall(node1, dir1) && removeWall(node2, dir2))
}

MazeNode* Maze::getNode(int x, int y) {
}

