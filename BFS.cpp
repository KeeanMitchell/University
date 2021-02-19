#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Grid
{
public:
    void initialise(int count);
    void printMaze(vector<vector<string>> maze);
    void printPosMaze(vector<vector<int>> maze);
    vector<vector<string>> distMaze;
    vector<vector<string>> Maze;
    vector<vector<int>> posMaze;

    void BFS(int rows, int cols, int sRow, int sCol);
    void checkNeigh(int row, int col, int dist);
    void solveMaze(int r, int c);

    bool foundG = false;

    list<int> rQueue, cQueue;
    int sRow;
    int sCol;
    int rows;
    int cols;
    int gRow;
    int gCol;
    int dr[4] = {1, 0, -1, 0};
    int dc[4] = {0, -1, 0, 1};
};

int main()
{
    Grid maze;
    vector<int> RandC;
    string numbers, grid;
    getline(cin, grid);
    stringstream X(grid);
    while (getline(X, numbers, ' '))
    {
        int num = stoi(numbers);
        RandC.push_back(num);
    }
    maze.rows = RandC[0];
    maze.cols = RandC[1];
    //std::cout << maze.rows << ' ' << maze.cols << endl;

    int count = 0;
    for (int i = 0; i < maze.rows; i++)
    {
        maze.initialise(count);
        //cout << count << endl;
        count++;
    }
    //cout << "here I am " << endl;
    for (int row = 0; row < maze.rows; row++)
    {
        for (int col = 0; col < maze.cols; col++)
        {
            if (maze.Maze[row][col] == "S")
            {
                maze.sRow = row;
                maze.sCol = col;
            }
        }
    }
    //cout << maze.sRow << ' ' << maze.sCol << endl;
    //cout << "get here please " << endl;
    maze.BFS(maze.rows, maze.cols, maze.sRow, maze.sCol);

    // maze.printPosMaze(maze.posMaze);
    // maze.printMaze(maze.distMaze);

    return 0;
}

void Grid::initialise(int count)
{
    vector<string> row;
    vector<int> r;
    string grid;
    getline(cin, grid);
    stringstream X(grid);
    char cElement;
    for (int j = 0; j < grid.size(); j++)
    {
        if (grid[j] == ' ')
        {
            row.push_back(" ");
        }
        else if (grid[j] == 'x')
        {
            row.push_back("x");
        }
        else if (grid[j] == 'S')
        {
            row.push_back("S");
        }
        else if (grid[j] == 'G')
        {
            row.push_back("G");
        }
        r.push_back(0);
    }
    Maze.push_back(row);
    distMaze.push_back(row);
    posMaze.push_back(r);
}

void Grid::BFS(int row, int col, int sRow, int sCol)
{
    //cout << "here" << endl;
    rQueue.push_back(sRow);
    cQueue.push_back(sCol);
    int dist;
    int count = 0;
    while (!rQueue.empty() && !cQueue.empty()) //count < 4)
    {
        int r = rQueue.front();
        int c = cQueue.front();
        rQueue.pop_front();
        cQueue.pop_front();

        if (distMaze[r][c] == "S")
        {
            dist = 1;
            checkNeigh(r, c, dist);
        }
        else
        {
            dist = stoi(distMaze[r][c]) + 1;
            //cout << "checking " << r << ' ' << c << endl;
            checkNeigh(r, c, dist);
        }
        if (foundG == true)
        {
            //std::cout << "yay " << gRow << ' ' << gCol << endl;
            //printPosMaze(posMaze);
            solveMaze(gRow, gCol);
            break;
        }
        if (rQueue.empty() && cQueue.empty())
        {
            cout << "No Path" << endl;
        }
        count++;
    }
}

void Grid::checkNeigh(int row, int col, int dist)
{
    for (int i = 0; i < 4; i++)
    {
        int r = row + dr[i];
        int c = col + dc[i];
        if (r >= rows || c >= cols || r < 0 || c < 0)
        {
            continue;
        }
        if (distMaze[r][c] == "G")
        {
            gRow = r;
            gCol = c;
            posMaze[r][c] = row * cols + col;
            //cout << "found it " << endl;
            foundG = true;
            //cout << foundG << endl;
            break;
        }
        if (distMaze[r][c] != " ")
        {
            continue;
        }
        else if (distMaze[r][c] == " ")
        {
            string num = to_string(0 + dist);
            distMaze[r][c] = num;
            posMaze[r][c] = row * cols + col;

            //printMaze(distMaze);
            rQueue.push_back(r);
            cQueue.push_back(c);
        }
    }
}

void Grid::solveMaze(int r, int c)
{
    int count = 0;
    bool reachedStart = false;
    while (reachedStart == false)
    {
        int nNum = posMaze[r][c];
        int num = r * cols + c;
        // cout << num << " num " << r << " row " << c << " col " << endl;
        // int nRow = (num - c) / cols;
        // int nCol = num - (nRow * cols);
        // cout << nRow << " new row " << nCol << " new col " << endl;
        // r = nRow;
        // c = nCol;
        if (nNum + 1 == num)
        {
            c = c - 1;
        }
        else if (nNum - 1 == num)
        {
            c = c + 1;
        }
        else if (nNum + cols == num)
        {
            r = r - 1;
        }
        else if (nNum - cols == num)
        {
            r = r + 1;
        }

        if (Maze[r][c] == "S")
        {
            printMaze(Maze);
            reachedStart = true;
        }
        else
        {
            Maze[r][c] = "*";
            //printMaze(Maze);
        }
        count++;
    }
}

void Grid::printMaze(vector<vector<string>> maze)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j == cols - 1)
            {
                std::cout << maze[i][j] << endl;
                continue;
            }
            std::cout << maze[i][j];
        }
    }
}

void Grid::printPosMaze(vector<vector<int>> maze)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j == cols - 1)
            {
                std::cout << '(' << maze[i][j] << ')' << endl;
                continue;
            }
            std::cout << '(' << maze[i][j] << ')';
        }
    }
}
