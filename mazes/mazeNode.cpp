#include "mazeNode.h"

MazeNode::MazeNode() {
    walls = 0xFF;
    visited = false;
}

~MazeNode::MazeNode() {
}

bool MazeNode::isVisited() {
    return visited;
}

bool MazeNode::visit() {
    if (visited) 
        return false;
    visited = true;
    return true;
}

bool MazeNode::hasWall(Direction dir) {
    //I think this works
    uint8_t mask = 1 << dir;
    return (walls & mask);
}

void MazeNode::removeWall(Direction  dir) {
    uint8_t mask = 1 << dir;
    walls &= ~mask;
}
