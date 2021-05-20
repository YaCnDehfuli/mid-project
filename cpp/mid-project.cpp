#include "mid-project.h"

Maze::Maze(size_t r, size_t c, double _percentage)
{
    rows = r;
    columns = c;
    percentage = _percentage;
    m = maze(rows, std::vector<int>(columns, 0));
    mb = maze(rows, std::vector<int>(columns, 0));
    sm = showing_maze(rows, std::vector<std::string>(columns, " "));
    parent_maze = maze(rows, std::vector<int>(columns, 0));
    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < columns; j++)
        {
            parent_maze[i][j]= (i*(columns))+j;
        }
    }
    vis = std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, false));
    dfs();
    randorm_choose();
    maze_show();
}

std::pair<size_t,size_t> Maze::point_to_cordinates(size_t point)
{
    size_t r = size_t(point/columns);
    size_t c = point-(r*columns);
    std::pair<size_t,size_t> cor{r,c};
    return cor;
}

size_t Maze::cordinates_to_point(std::pair<size_t,size_t> cori)
{
    return parent_maze[cori.first][cori.second];
}


void Maze::path_show(maze _m)
{
    std::cout << "\n";
    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < columns; j++)
        {
            std::cout << std::setw(4) << std::left << "|" << std::setw(4) << std::fixed << _m[i][j];
        }
        std::cout << "|";
        std::cout << std::endl;
        for (size_t i{}; i < columns; i++)
            std::cout << "--------";
        std::cout << std::endl;
    }
}
void Maze::maze_show()
{
    std::cout << "\n";
    for (size_t i{}; i < columns; i++)
        std::cout << "------";
    std::cout << std::endl;
    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < columns; j++)
        {
            std::cout << std::setw(2) << std::left << "|" << std::setw(4) << std::fixed << sm[i][j];
        }
        std::cout << "|";
        std::cout << std::endl;
        for (size_t i{}; i < columns; i++)
            std::cout << "------";
        std::cout << std::endl;
    }
}

bool Maze::is_valid(std::pair<size_t, size_t> p)
{
    if(p.first <0 || p.second<0)
        return false;
    else if (p.first >= rows || p.second >= columns)
        return false;
    else if (vis[p.first][p.second])
        return false;
    else if (m[p.first][p.second] == -100)
        return false;
    else
        return true;
}

void Maze::dfs()
{
    std::pair<size_t, size_t> starting_cell = {0, 0};
    std::pair<size_t, size_t> Goal_cell = {rows - 1, columns - 1};
    std::stack<std::pair<size_t, size_t>> st;
    std::pair<size_t, size_t> current_cell = starting_cell;
q:
    st.push(current_cell);
    size_t counter{1};

    while (!st.empty())
    {
        current_cell = st.top();
        st.pop();

        if (is_valid(current_cell))
        {
            vis[current_cell.first][current_cell.second] = true;
            m[current_cell.first][current_cell.second] = counter;
            counter++;
            dfs_cells_to_goal = counter;
            if (current_cell == Goal_cell)
            {
                if (counter < (size_t(rows + columns) * 1.4))
                {
                    break;
                }
                else
                {
                    goto n;
                }
            }
        }
        else
            continue;

        std::pair<size_t, size_t> up{current_cell.first, current_cell.second - 1};
        std::pair<size_t, size_t> down{current_cell.first, current_cell.second + 1};
        std::pair<size_t, size_t> left{current_cell.first - 1, current_cell.second};
        std::pair<size_t, size_t> right{current_cell.first + 1, current_cell.second};

        std::vector<std::pair<size_t, size_t>> directions{up, down, left, right};
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

        for (auto &i : directions)
            st.push(i);
    }
n:
    if (m[Goal_cell.first][Goal_cell.second] > int((rows + columns) * 1.4))
    {
        while (!st.empty())
        {
            st.pop();
        }
        for (size_t i{}; i < vis.size(); i++)
        {
            for (size_t j{}; j < vis[0].size(); j++)
            {
                vis[i][j] = false;
            }
        }
        std::pair<size_t, size_t> starting_cell = {0, 0};
        current_cell = starting_cell;
        counter = 1;
        for (size_t i{}; i < rows; i++)
        {
            for (size_t j{}; j < columns; j++)
            {
                m[i][j] = 0;
            }
        }
        goto q;
    }
}

void Maze::randorm_choose()
{
    size_t counter{};
    while (counter <= size_t((rows * columns - dfs_cells_to_goal) * percentage / 100) + 1)
    {
        size_t random_row = rand() % (rows);
        size_t random_column = rand() % (columns);
        if (m[random_row][random_column] == 0)
        {
            sm[random_row][random_column] = "***";
            m[random_row][random_column] = -100;
            mb[random_row][random_column] = -100;
            counter++;
        }
    }
}

bool Maze::is_valid_prime(std::pair<size_t, size_t> p)
{
    if(p.first <0 || p.second<0)
        return false;
    else if (p.first >= rows || p.second >= columns)
        return false;
    else if (mb[p.first][p.second] == -100)
        return false;
    else
        return true;
}

void Maze::bfs()
{

    // Maze* mb = new Maze(rows,columns,percentage);
    std::pair<size_t, size_t> starting_cell = {0, 0};
    std::pair<size_t, size_t> Goal_cell = {rows - 1, columns - 1};

    std::queue<std::pair<size_t, size_t>> q;
    std::pair<size_t, size_t> current_cell = starting_cell;
    // q:
    for (size_t i{}; i < vis.size(); i++)
    {
        for (size_t j{}; j < vis[0].size(); j++)
        {
            vis[i][j] = false;
        }
    }



    for (size_t i{}; i < rows; i++)
    {
        for (size_t j{}; j < columns; j++)
        {
            if (mb[i][j] != -100) //|| m[rows][columns] != 0)
            {
                mb[i][j] = 0;
            }
        }
    }
    std::vector<size_t> parent_vector (rows*columns);
    std::vector<size_t> route;

    q.push(current_cell);
    vis[current_cell.first][current_cell.second] = true;
    mb[current_cell.first][current_cell.second] = 1;
    // counter--;
    parent_vector[0]=-1;

    while (!q.empty())
    {
        current_cell = q.front();
        q.pop();

        std::pair<size_t, size_t> up{current_cell.first, current_cell.second - 1};
        std::pair<size_t, size_t> down{current_cell.first, current_cell.second + 1};
        std::pair<size_t, size_t> left{current_cell.first - 1, current_cell.second};
        std::pair<size_t, size_t> right{current_cell.first + 1, current_cell.second};
        std::vector<std::pair<size_t, size_t>> directions{up, down, left, right};
        
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));
                
        for (auto &i : directions)
        {
            if (is_valid(i))
            {
                q.push(i);
                vis[i.first][i.second] = true;
                // mb[i.first][i.second] = (i.first + i.second) + 1;
                parent_vector[(parent_maze[i.first][i.second])]=parent_maze[current_cell.first][current_cell.second];

                if (i == Goal_cell)
                {
                    std::cout<<std::endl;
                    bfs_cells_to_goal = (i.first + i.second) + 1;
                    mb[i.first][i.second]=bfs_cells_to_goal;
                    std::cout << "\n"
                              << "I found the shortest path !!!" << std::endl;
                    std::pair <size_t,size_t> corr =i;
                    size_t pw{1};
                    while(pw!=0)
                    {
                        pw = parent_vector[cordinates_to_point(corr)];
                        route.push_back(pw);
                        corr=point_to_cordinates(pw);
                    }
                    break;
                }
            }

            else
                continue;
        }
    }
    for(auto i:route)
    {
        mb[point_to_cordinates(i).first][point_to_cordinates(i).second]=bfs_cells_to_goal-1;
        bfs_cells_to_goal--;
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
}