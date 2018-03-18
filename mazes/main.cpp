#include "maze.h"
#include "nodeStack.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    srand(clock());
    if (argc < 3) {
        printf("Usage: %s <width> <height>\n", argv[0]);
        exit(1);
    }
    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    Maze* my_maze = new Maze(w, h);
    
    //starting x will either be 0 or width-1
    int num_start = rand() % (2 * (w + h - 2));
    int start_x;
    int start_y;
    printf("num_start:%d\n", num_start);
    if (num_start > 0 && num_start <= w) {
        start_x = num_start;
        start_y = 0;
    }
    if (num_start > w && num_start <= w+h-1) {
        start_x = w-1;
        start_y = num_start - w;
    }
    if (num_start > w+h-1 && num_start <= w+h-1+w-1) {
        start_x = num_start - (w+h-1);
        start_y = h-1;
    }
    if (num_start > w+h-1+w-1 && num_start <= w+h-1+w-1+h-2) {
        start_x = 0;
        start_y = num_start - (w+h-1+w-1);
    }
    //int start_x = (rand() % 2) * (width-1);
    //int start_y = (rand() % 2) * (height-1);
    printf("starting: x:%d, y:%d\n", start_x, start_y);
    MazeNode* curr_node = my_maze->getNode(start_x, start_y);
    NodeStack* my_stack = new NodeStack();
    my_stack->push(curr_node);
    MazeNode* neighbors[4];
    int curr_x = start_x;
    int curr_y = start_y;
    MazeNode* next_node = NULL;
    //visit the first node and push it onto the stack
    //get a neighbor that is unvisited, and make him the current node
    //then repeat this process until the stack is empty
    while (!my_stack->isEmpty()) {
        //my_maze->drawMaze();
        //printf("\n");
        if (curr_node == NULL)
            printf("fuuuuck\n");
        curr_node->visit();
        curr_x = curr_node->getX();
        curr_y = curr_node->getY();
        neighbors[0] = my_maze->getNode(curr_x+1, curr_y);
        neighbors[1] = my_maze->getNode(curr_x-1, curr_y);
        neighbors[2] = my_maze->getNode(curr_x, curr_y+1);
        neighbors[3] = my_maze->getNode(curr_x, curr_y-1);
        //we'll do a small version of reservior sampling
        int valid_seen = 0;
        next_node = NULL;
        for (int i = 0; i < 4; i++) {
            if (neighbors[i] == NULL || neighbors[i]->isVisited())
                continue;
            valid_seen++;
            if (rand() % valid_seen == 0)
                next_node = neighbors[i];
        }
        //if next_node is NULL, then no valid neighbor exists
        if (next_node == NULL) {
            my_stack->pop();
            curr_node = my_stack->peek();
        }
        //if it isn't null, then break the wall between the two nodes
        else {
            my_maze->removeWall(curr_x, curr_y, next_node->getX(), next_node->getY());
            //now push the next node and make it the current node
            my_stack->push(next_node);
            curr_node = next_node;
            next_node = NULL;
        }
    }
    my_maze->getNode(0, 0)->removeWall(NORTH);
    my_maze->getNode(w-1, h-1)->removeWall(SOUTH);
    my_maze->drawMaze();
}
