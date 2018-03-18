#include "maze.h"
#include "stdio.h"

Maze::Maze(int width, int height) {
    w = width;
    h = height;
    maze = (MazeNode**)malloc(sizeof(MazeNode*)*w*h);
    //init all nodes
    int curr_ind = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            maze[curr_ind] = new MazeNode();
            maze[curr_ind]->setX(x);
            maze[curr_ind]->setY(y);
            curr_ind++;
        }
    }
}

Maze::~Maze() {
    for (int i = 0; i < w*h; i++) {
        delete maze[i];
    }
    free(maze);
}

bool Maze::allVisited() {
    for (int i = 0; i < w*h; i++) {
        if (!maze[i]->isVisited())
            return false;
    }
    return true;
}
bool Maze::visit(int x, int y) {
    return visit(getNode(x, y));
}

bool Maze::visit(MazeNode* node) {
    if (node == NULL)
        return false;
    node->visit();
}

bool Maze::removeWall(int x, int y, Direction dir) {
    MazeNode* node1 = getNode(x, y);
    MazeNode* node2;
    Direction dir2;
    switch (dir) {
        case NORTH:
            node2 = getNode(x, y+1);
            dir2 = SOUTH;
            break;
        case NORTHWEST:
            node2 = getNode(x-1, y+1);
            dir2 = SOUTHEAST;
            break;
        case NORTHEAST:
            node2 = getNode(x+1, y+1);
            dir2 = SOUTHWEST;
            break;
        case SOUTH:
            node2 = getNode(x, y-1);
            dir2 = NORTH;
            break;
        case SOUTHWEST:
            node2 = getNode(x-1, y-1);
            dir2 = NORTHEAST;
            break;
        case SOUTHEAST:
            node2 = getNode(x+1, y-1);
            dir2 = NORTHWEST;
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
            node2=NULL;
    }
    if (! (node1 && node2))
        return false;

    node1->removeWall(dir);
    node2->removeWall(dir2);
    return true;
}


bool Maze::removeWall(int x1, int y1, int x2, int y2) {
    MazeNode* node1 = getNode(x1, y1);
    if (!node1)
        return false;
    MazeNode* node2 = getNode(x2, y2);
    if (!node2)
        return false;
    int xdiff = x1 - x2;
    int ydiff = y1 - y2;
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
        dir1 = NORTHEAST;
        dir2 = SOUTHWEST;
    }
    else if (xdiff == -1 && ydiff == 1) {
        dir1 = NORTHWEST;
        dir2 = SOUTHEAST;
    }
    else if (xdiff == 0 && ydiff == -1) {
        dir1 = SOUTH;
        dir2 = NORTH;
    }
    else if (xdiff == 1 && ydiff == -1) {
        dir1 = SOUTHEAST;
        dir2 = NORTHWEST;
    }
    else if (xdiff == -1 && ydiff == -1) {
        dir1 = SOUTHWEST;
        dir2 = NORTHEAST;
    }
    else if (xdiff == 1 && ydiff == 0) {
        dir1 = EAST;
        dir2 = WEST;
    }
    else if (xdiff == -1 && ydiff == 0) {
        dir1 = WEST;
        dir2 = EAST;
    }

    node1->removeWall(dir1);
    node2->removeWall(dir2);
    return true;
}

MazeNode* Maze::getNode(int x, int y) {
    if (x < 0 || x > w-1 || y < 0 || y > h-1)
        return NULL;
    int offset = y*w + x;
    return maze[offset];
}

void Maze::drawMaze() {
    //okay so each cell is a 3x3 grid.
    //draw the center empty if it is visited
    //draw walls empty if they are broken
    int draw_w = w*3;
    int draw_h = h*3;
    int** draw_pattern = new int*[draw_w];
    for (int i = 0; i < draw_w; i++) {
        draw_pattern[i] = new int[draw_h];
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            MazeNode* node = getNode(x, y);
            uint8_t walls = node->getWalls();
            int pat_x = x*3 + 1;
            int pat_y = y*3 + 1;
            //okay draw this cell
            //put a 0 for no wall
            draw_pattern[pat_x][pat_y] = !node->isVisited();
            //draw_pattern[pat_x][pat_y] = 1;
            draw_pattern[pat_x][pat_y-1] = walls & 0x01;
            draw_pattern[pat_x-1][pat_y-1] = walls & 0x02;
            draw_pattern[pat_x-1][pat_y] = walls & 0x04;
            draw_pattern[pat_x-1][pat_y+1] = walls & 0x08;
            draw_pattern[pat_x][pat_y+1] = walls & 0x10;
            draw_pattern[pat_x+1][pat_y+1] = walls & 0x20;
            draw_pattern[pat_x+1][pat_y] = walls & 0x40;
            draw_pattern[pat_x+1][pat_y-1] = walls & 0x80;
        }
    }
    //now draw form the generated pattern
    for (int y = 0; y < h*3; y++) {
        for (int x = 0; x < w*3; x++) {
            if (draw_pattern[x][y] != 0)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }
    for (int i = 0; i < draw_w; i++) {
        delete[] draw_pattern[i];
    }
    delete[] draw_pattern;
}
