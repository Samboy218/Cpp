class maze {
    public:
        bool allVisited();
        bool visit(int x, int y);
        bool visit(mazeNode* node);
        //bunch of overloaded functions for this
        bool removeWall(mazeNode* node, Direction dir);
        bool removeWall(int x, int y, Direction dir);
        bool removeWall(mazeNode* node1, mazeNode* node2);
        bool removeWall(int x1, int y1, int x2, int y2);
        mazeNode* getNode(int x, int y);

    private:
        mazeNode* maze;
        int w;
        int h;

}

