#ifndef MAZE_NODE_H
#define MAZE_NODE_H
enum Direction = {NORTH, NORTH-EAST, EAST, SOUTH-EAST, SOUTH, SOUTH-WEST, WEST, NORTH-WEST} 
class mazeNode {
    public:
        mazeNode();
        ~mazeNode();
        bool isVisited();
        bool visit();
        bool hasWall(Direction dir);
        void removeWall(Direction  dir);


    private:
        //each bit says whether there is a wall
        //0x01 is N
        //0x02 is NE
        //0x04 is E
        //0x08 is SE
        //0x10 is S
        //0x20 is SW
        //0x40 is W
        //0x80 is NW
        uint8_t walls;
        bool visited;
}
#endif
