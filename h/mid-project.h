#ifndef MID_PROJECT_H
#define MID_PROJECT_H
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
// #include <bits/stdc++.h>
#include <queue>

class Maze
{
    using maze = std::vector<std::vector<int>>;
    using showing_maze = std::vector<std::vector<std::string>>;
    
    public:
        Maze(size_t,size_t,double);
        void maze_show();
        void path_show(maze);
        void dfs();
        void bfs();
        std::vector<std::vector<bool>> vis;
        bool is_valid(std::pair<size_t,size_t> p);
        bool is_valid_prime(std::pair<size_t,size_t> p);
        void randorm_choose();
        showing_maze sm;
        maze m;
        maze mb;
        size_t dfs_cells_to_goal;
        size_t bfs_cells_to_goal;
    private:
        size_t rows;
        size_t columns;
        double percentage;
};

#endif