#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

// 1/LIFE_CHANCE is the probability a cell will begin with life
#define LIFE_CHANCE 5

// the size, in pixels, of each cell
#define CELL_H 5
#define CELL_W 5

//the speed to run at (FPS)
#define FPS_RUN 30

//how many generations to wait until we restart
#define NEXT_AT 1500


enum valid_colors {
    COLOR_BLACK, COLOR_RED,
    COLOR_GREEN, COLOR_BLUE,
    COLOR_YELLOW, COLOR_MAGENTA,
    COLOR_CYAN, COLOR_WHITE,
    NUM_COLORS
};

class GOLBoard
{
    public:
    GOLBoard(int w, int h);
    ~GOLBoard();
    void setCell(int x, int y);
    void clearCell(int x, int y);
    unsigned char cellState(int x, int y);
    unsigned char countNeighbors(int x, int y);
    void step();
    void init(int aliveChance);
    int getW();
    int getH();
    void drawBoard();


    private:
    unsigned char* board;
    unsigned char* tempBoard;
    int w;
    int h;
    int lengthB;
};

int main() 
{
    srandom(time(NULL));
    char counter[20];
    int generation = 0;

    //now we can make art
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    int gridW = size.ws_col - 2;
    int gridH = size.ws_row - 3;
    GOLBoard board(gridW, gridH);
    board.init(LIFE_CHANCE);

#pragma GCC diagnostic ignored "-Wdiv-by-zero"
    int timeWait = 0;
    if (FPS_RUN != 0)
        timeWait = CLOCKS_PER_SEC / FPS_RUN;
    clock_t now;
    clock_t previous = clock();

    
    while(1) 
    {
        now = clock();
        if ((now - previous) < timeWait)
        {
            //printf("had to wait %d us at gen %d\n", timeWait-(now-previous), generation);
            usleep(timeWait - (now - previous));
        }
        previous = now;

        //draw a generation
        board.drawBoard();
        sprintf(counter, "Generation: %d", generation);
        //XSetForeground(dpy, g, xcolors[liveColor].pixel);
        //XDrawString(dpy, root, g, 50, 50, counter, strlen(counter));
        generation++;
        board.step();

        if (generation >= NEXT_AT) 
        {
            board.init(LIFE_CHANCE);
            generation = 0;
        }
    }
}

void GOLBoard::drawBoard()
{
    unsigned char* cellPtr;
    cellPtr = board;
    printf("|");
    for (int i = 0; i < w; i++)
        printf("-");
    printf("|\n");
    for (int y = 0; y < h; y++)
    {
        printf("|");
        for (int x = 0; x < w; x++)
        {
            if ((*cellPtr) & 0x01)
            {
                //cell is alive
                printf("#");
            }
            else
            {
                //cell is dead
                printf(" ");
            }
            cellPtr++;
        }
        printf("|\n");
    }
    printf("|");
    for (int i = 0; i < w; i++)
        printf("-");
    printf("|");
    printf("\n");
} 

GOLBoard::GOLBoard(int x, int y)
{
    w = x;
    h = y;
    lengthB = w*h;
    board = new unsigned char[lengthB];
    tempBoard = new unsigned char[lengthB];    
    memset(board, 0, lengthB);
    memset(tempBoard, 0, lengthB);
}

GOLBoard::~GOLBoard()
{
    delete[] board;
    board = NULL;
    delete[] tempBoard;
    tempBoard = NULL;
}

//turn cell on, and update neighbors
void GOLBoard::setCell(int x, int y)
{
    if ( x >= w || y >= h)
        return;

    unsigned char* cellPtr = board + (y*w) + x;
    int xoleft, xoright, youp, yodown;
    
    if (x == 0)
        xoleft = w - 1;
    else
        xoleft = -1;
    if (y == 0)
        youp = lengthB - w;
    else
        youp = -w;
    if (x == (w-1))
        xoright = -(w - 1);
    else
        xoright = 1;
    if (y == h-1)
        yodown = -(lengthB - w);
    else
        yodown = w;

    *(cellPtr) |= 0x01;
    *(cellPtr + youp + xoleft) += 2;
    *(cellPtr + youp) += 2;
    *(cellPtr + youp + xoright) += 2;
    *(cellPtr + xoleft) += 2;
    *(cellPtr + xoright) += 2;
    *(cellPtr + yodown + xoleft) += 2;
    *(cellPtr + yodown) += 2;
    *(cellPtr + yodown + xoright) += 2;

}

void GOLBoard::clearCell(int x, int y)
{
    if ( x >= w || y >= h)
        return;

    unsigned char* cellPtr = board + (y*w) + x;
    int xoleft, xoright, youp, yodown;
    
    if (x == 0)
        xoleft = w - 1;
    else
        xoleft = -1;
    if (y == 0)
        youp = lengthB - w;
    else
        youp = -w;
    if (x == (w-1))
        xoright = -(w - 1);
    else
        xoright = 1;
    if (y == h-1)
        yodown = -(lengthB - w);
    else
        yodown = w;

    *(cellPtr) &= 0xFE;
    *(cellPtr + youp + xoleft) -= 2;
    *(cellPtr + youp) -= 2;
    *(cellPtr + youp + xoright) -= 2;
    *(cellPtr + xoleft) -= 2;
    *(cellPtr + xoright) -= 2;
    *(cellPtr + yodown + xoleft) -= 2;
    *(cellPtr + yodown) -= 2;
    *(cellPtr + yodown + xoright) -= 2;

}

unsigned char GOLBoard::cellState(int x, int y)
{
    unsigned char* cellPtr;
    cellPtr = board + (y*w) + x;
    return *(cellPtr) & 0x01;
}

unsigned char GOLBoard::countNeighbors(int x, int y)
{
    unsigned char* cellPtr;
    cellPtr = board + (y*w) + x;
    return *(cellPtr) >> 1;
}

void GOLBoard::step()
{
    unsigned int x, y, count;
    unsigned char*  cellPtr;

    memcpy(tempBoard, board, lengthB);

    cellPtr = tempBoard;

    for (y = 0; y < h; y++)
    {
nextRow:
        x = 0;
        while (x < w)
        {
            while (cellPtr == 0)
            {
                cellPtr++;
                x++;
                if (x >=w)
                    goto nextRow;
                    //wow, the only valid use for goto in c++; I never thought
                    //I would see this day
            }
            //cell was not 0, need to compute
            count = *cellPtr >> 1;
            if (*cellPtr & 0x01)
            {
                //cell is on, kill it unless it has 2 or 3 neighbors
                if ((count != 2) && (count !=3))
                {
                    clearCell(x, y);
                }
            }
            else
            {
                //cell is off, bring it to life if it has 3 neighbors
                if (count == 3)
                {
                    setCell(x, y);
                }
            }
            cellPtr++;
            x++;
        }
    }
}

void GOLBoard::init(int aliveChance)
{
    //init the board randomly according to the defined frequency
    //probability is 1/aliveChance
    unsigned char* cellPtr;
    cellPtr = board;
    memset(board, 0, lengthB);
    memset(tempBoard, 0, lengthB);
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            if (random()%aliveChance == 0)
            {
                setCell(x, y);
            }
        }
    }

}

int GOLBoard::getW()
{
    return w;
}

int GOLBoard::getH()
{
    return h;
}
