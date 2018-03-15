#include "mazeNode.h"

mazeNode::mazeNode() {
    walls = 0xFF;
    visited = false;
}

~mazeNode::mazeNode() {
}

bool mazeNode::isVisited() {
    return visited;
}

bool mazeNode::visit() {
    if (visited) 
        return false;
    visited = true;
    return true;
}

bool mazeNode::hasWall(Direction dir) {
    //I think this works
    uint8_t mask = 1 << dir;
    return (walls & mask);
}

void mazeNode::removeWall(Direction  dir) {
    uint8_t mask = 1 << dir;
    walls &= ~mask;
}
