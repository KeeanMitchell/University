#include <iostream>
#include <vector>
#include <sstream>
#include <istream>
#include <string>
#include <math.h>
#include <chrono>
#include <ctime>
#include <cmath>

using namespace std;

class Timer
{
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
};

string itosConvert(int i)
{
    if (i == 1)
        return "1";
    if (i == 2)
        return "2";
    if (i == 3)
        return "3";
    if (i == 4)
        return "4";
    if (i == 5)
        return "5";
    if (i == 6)
        return "6";
    if (i == 7)
        return "7";
    if (i == 8)
        return "8";
    if (i == 9)
        return "9";
    if (i == 10)
        return "A";
    if (i == 11)
        return "B";
    if (i == 12)
        return "C";
    if (i == 13)
        return "D";
    if (i == 14)
        return "E";
    if (i == 15)
        return "F";
    if (i == 16)
        return "G";
    if (i == 17)
        return "H";
    if (i == 18)
        return "I";
    if (i == 19)
        return "J";
    if (i == 20)
        return "K";
    if (i == 21)
        return "L";
    if (i == 22)
        return "M";
    if (i == 23)
        return "N";
    if (i == 24)
        return "O";
    if (i == 25)
        return "P";
}

class sudokuGrid
{
public:
    vector<vector<string>> sgrid;
    vector<vector<string>> copyGrid1;
    vector<vector<string>> copyGrid2;
    vector<vector<string>> copyOrigGrid;
    void initialise();
    void defValues();
    void defCheckValues();
    void placeValue(int row, int col);
    int count = 0;

    //test cases 1
    bool testValRow(int row, string num);
    bool testValCol(int col, string num);
    bool testValBox(int row, int col, string num);
    //checking if value is already in row, col, box
    bool checkValue(int row, int col, string num);
    //test cases 2 ( def values )
    bool onlyPlaceInBox(int row, int col, string num);
    bool onlyPlaceInRow(int row, string num);
    bool onlyPlaceInCol(int col, string num);
    bool onlyValue(int row, int col, string num);
    //checking grid for empty spaces
    bool isGridFull(vector<vector<string>> aGrid);
    //after defvalues all in
    bool finishingSudoku();


};

int main()
{
    Timer timer;
    sudokuGrid myGrid;
    vector<string> rows;
    string numbers, grid;
    getline(cin, grid);
    stringstream X(grid);
    while (getline(X, numbers, ' '))
    {
        rows.push_back(numbers);
        myGrid.count += 1;
    }
    myGrid.sgrid.push_back(rows);
    for (int gridSize = 0; gridSize < myGrid.count - 1; gridSize++)
        myGrid.initialise();
    timer.start();
    
    for (int i = 0; i < myGrid.count; i++)
    {
        myGrid.copyGrid1.push_back(myGrid.sgrid[i]);
    }

    bool copyGridSameAsOrig = false;
    while (copyGridSameAsOrig == false)
    {
        myGrid.defValues();
        myGrid.defCheckValues();
        int breakCount = 0;
        for (int r = 0; r < myGrid.count; r++)
        {
            for (int c = 0; c < myGrid.count; c++)
            {
                if (myGrid.copyGrid1[r][c] == myGrid.sgrid[r][c])
                {
                    breakCount += 1;
                }
                else if (myGrid.copyGrid1[r][c] != myGrid.sgrid[r][c])
                {
                    myGrid.copyGrid1[r][c] = myGrid.sgrid[r][c];
                    // myGrid.copyGrid2[r][c] = myGrid.sgrid[r][c];
                    // myGrid.copyOrigGrid[r][c] = myGrid.sgrid[r][c];
                }
            }
        }
        //cout << breakCount << " breakcount" << endl;
        if (breakCount == myGrid.count * myGrid.count)
        {
            //timer.stop();
            //cout << timer.elapsedMilliseconds() << " this is the time after def value" << endl;
            copyGridSameAsOrig = true;
        }
    }
    
    if (myGrid.finishingSudoku() == true)
    {
        timer.stop();
        cout << timer.elapsedMilliseconds() << " this is the time" << endl;
        //cout << "yay" << endl;
        for (int row = 0; row < myGrid.count; row++)
        {
            for (int col = 0; col < myGrid.count; col++)
                if (col == 8){
                    cout << myGrid.sgrid[row][col];
                }
                else
                    cout << myGrid.sgrid[row][col] << ' ';
            cout << endl;
        }
    }
    else
        cout << "No Solution" << endl;

    return 0;
}

bool sudokuGrid::finishingSudoku()
{
    // int row, col;
    for (int r = 0; r < count; r++)
    {
        for (int c = 0; c < count; c++)
        {
            if (sgrid[r][c] == "0")
            {
                
                for (int i = 1; i <= count; i++)
                {
                    string num = itosConvert(i);
                    if (checkValue(r, c, num))
                    {
                        //cout << "getting here" << endl;
                        sgrid[r][c] = num;
                        //cout << sgrid[r][c] << endl;
                        if (finishingSudoku())
                        {
                            //cout << "returned true" << endl;
                            return true;
                        }
                        sgrid[r][c] = "0";
                    }
                }
                //cout << "returned false" << endl;
                return false;
            }
        }
    }
}

void sudokuGrid::initialise()
{
    vector<string> rows;
    string numbers, grid;
    getline(cin, grid);
    stringstream X(grid);
    while (getline(X, numbers, ' '))
    {
        rows.push_back(numbers);
    }
    sgrid.push_back(rows);
}

void sudokuGrid::defValues()
{
    for (int row = 0; row < count; row++)
    {
        for (int col = 0; col < count; col++)
        {
            if (sgrid[row][col] != "0")
            {
                //cout << "place filled " << row << ' ' << col << endl;
                continue;
            }
            if (sgrid[row][col] == "0")
            {
                //cout << row << ' ' << col << " no value yet" << endl;
                placeValue(row, col);
            }
        }
    }
}

void sudokuGrid::defCheckValues()
{

    for (int row = 0; row < count; row++)
    {
        for (int col = 0; col < count; col++)
        {
            int checkCount = 0;
            string storeNum = "0";
            for (int i = 1; i <= count; i++)
            {
                string num = itosConvert(i);
                if (sgrid[row][col] != "0")
                {
                    //cout << "place filled " << row << ' ' << col << endl;
                    continue;
                }
                if (sgrid[row][col] == "0")
                {
                    if (checkValue(row, col, num) == true)
                    {
                        checkCount += 1;
                        //cout << "checked number " << num << " chief" << endl;
                        if (checkCount > 1)
                        {
                            //cout << "sorry chief " << row << ' ' << col << endl;
                            storeNum = "0";
                            //sgrid[row][col] = storeNum;
                            //break;
                        }
                        else if (checkCount == 1)
                        {
                            //cout << num << " is the only one that works chief" << endl;
                            storeNum = num;
                        }
                        // sgrid[row][col] = storeNum;
                    }
                    //cout << "checked " << checkCount << " numbers chief" << endl;
                }
            }
            if (checkCount == 1)
            {
                sgrid[row][col] = storeNum;
                //cout << "row " << row << " col " << col << " value" << storeNum << endl;
            }
        }
    }
}

void sudokuGrid::placeValue(int row, int col)
{
    for (int i = 1; i <= count; i++)
    {
        int checkCount = 0;
        string num = itosConvert(i);
        //cout << "checking value " << num << "row " << row << "col " << col << endl;
        if (checkValue(row, col, num) == true)
        {
            if (onlyValue(row, col, num) == true)
            {
                //cout << "show me" << endl;
                sgrid[row][col] = num;
                break;
            }
        }
    }
}

bool sudokuGrid::onlyValue(int row, int col, string num)
{
    if (checkValue(row, col, num) == true)
    {
        if (onlyPlaceInRow(row, num) == true)
        {
            //cout << "placed only place in row " << num << endl;
            return true;
        }
        else if (onlyPlaceInCol(col, num) == true)
        {
            //cout << "placed only place in col " << num << endl;
            return true;
        }
        else if (onlyPlaceInBox(row, col, num) == true)
        {
            //cout << "placed only value in box" << endl;
            return true;
        }
    }
    return false;
}

bool sudokuGrid::checkValue(int row, int col, string num)
{
    int N = sqrt(count);
    if (!testValRow(row, num) && !testValCol(col, num) && !testValBox(row, col, num))
        return true;
    return false;
}

bool sudokuGrid::onlyPlaceInRow(int row, string num)
{
    int rowCount = 0;
    for (int c = 0; c < count; c++)
    {
        if (sgrid[row][c] != "0")
        {
            continue;
        }
        if (!testValCol(c, num) && !testValBox(row, c, num))
        {
            rowCount += 1;
            // cout << "check was true for " << row << ' ' << c << endl;
        }
        if (rowCount > 1)
        {
            //cout << "too many chief " << rowCount << " checking number " << num << endl;
            return false;
        }
    }
    return true;
}

bool sudokuGrid::onlyPlaceInCol(int col, string num)
{
    int colCount = 0;
    for (int r = 0; r < count; r++)
    {
        if (sgrid[r][col] != "0")
            continue;
        if (!testValRow(r, num) && !testValBox(r, col, num))
        {

            colCount += 1;
            //cout << "colCount " << colCount << endl;
        }
        if (colCount > 1)
            return false;
    }
    return true;
}

bool sudokuGrid::onlyPlaceInBox(int row, int col, string num)
{
    int copyRow;
    int copyCol;
    int boxCount = 0;
    if (row < sqrt(count))
    {
        copyRow = 0;
        if (col < sqrt(count))
        {
            copyCol = 0;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            copyCol = sqrt(count);
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                    {
                        boxCount += 1;
                    }
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            copyCol = sqrt(count) * 2;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            copyCol = sqrt(count) * 3;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            copyCol = sqrt(count) * 4;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
    }
    if (row >= sqrt(count) && row < sqrt(count) * 2)
    {
        copyRow = sqrt(count);
        if (col < sqrt(count))
        {
            copyCol = 0;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            copyCol = sqrt(count);
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            copyCol = sqrt(count) * 2;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            copyCol = sqrt(count) * 3;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            copyCol = sqrt(count) * 4;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
    }
    if (row >= sqrt(count) * 2 && row < sqrt(count) * 3)
    {
        copyRow = sqrt(count) * 2;
        if (col < sqrt(count))
        {
            copyCol = 0;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            copyCol = sqrt(count);
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            copyCol = sqrt(count) * 2;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            copyCol = sqrt(count) * 3;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            copyCol = sqrt(count) * 4;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
    }
    if (row >= sqrt(count) * 3 && row < sqrt(count) * 4)
    {
        copyRow = sqrt(count) * 2;
        if (col < sqrt(count))
        {
            copyCol = 0;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            copyCol = sqrt(count);
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            copyCol = sqrt(count) * 2;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            copyCol = sqrt(count) * 3;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            copyCol = sqrt(count) * 4;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
    }
    if (row >= sqrt(count) * 4 && row < sqrt(count) * 5)
    {
        copyRow = sqrt(count) * 2;
        if (col < sqrt(count))
        {
            copyCol = 0;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            copyCol = sqrt(count);
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            copyCol = sqrt(count) * 2;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            copyCol = sqrt(count) * 3;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            copyCol = sqrt(count) * 4;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[copyRow + r][copyCol + c] != "0")
                    {
                        continue;
                    }
                    if (!testValRow(copyRow + r, num) && !testValCol(copyCol + c, num))
                        boxCount += 1;
                }
            }
            if (boxCount > 1)
                return false;
            return true;
        }
    }
}

bool sudokuGrid::testValCol(int col, string num)
{
    for (int r = 0; r < count; r++)
    {
        //cout << row << ' ' << col << ' ' << sgrid[row][col] << "/ ";
        if (sgrid[r][col] == num)
        {
            return true;
        }
    }
    return false;
}

bool sudokuGrid::testValRow(int row, string num)
{
    for (int c = 0; c < count; c++)
    {
        //cout << row << ' ' << col << ' ' << sgrid[row][col] << "/ ";
        if (sgrid[row][c] == num)
        {
            return true;
        }
    }
    //cout << "no = value in rows" << endl;
    return false;
}

bool sudokuGrid::testValBox(int row, int col, string num)
{
    // for (int row = 0; row < sqrt(count); row++)
    //     for (int col = 0; col < sqrt(count); col++)
    //     {
    //         //cout << row << '+' << startRow << ' ' << col << '+' << startCol << " is this working" << endl;
    //         if (sgrid[row + startRow][col + startCol] == num)
    //             return true;
    //     }
    // return false;

    if (row < sqrt(count))
    {
        row = 0;
        if (col < sqrt(count))
        {
            col = 0;
            //cout << "block one" << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box one works" << endl;
            return false;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            col = sqrt(count);
            //cout << "block two " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box two works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            col = sqrt(count) * 2;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            col = sqrt(count) * 3;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            col = sqrt(count) * 4;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
    }
    if (row >= sqrt(count) && row < sqrt(count) * 2)
    {
        row = sqrt(count);
        if (col < sqrt(count))
        {
            col = 0;
            //cout << "block four " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box four works" << endl;
            return false;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            col = sqrt(count);
            //cout << "block five " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box five works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            col = sqrt(count) * 2;
            //cout << "block six " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box six works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            col = sqrt(count) * 3;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            col = sqrt(count) * 4;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
    }
    if (row >= sqrt(count) * 2 && row < sqrt(count) * 3)
    {
        row = sqrt(count) * 2;
        if (col < sqrt(count))
        {
            col = 0;
            //cout << "block seven " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box seven works" << endl;
            return false;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            col = sqrt(count);
            //cout << "block eight " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box eight works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            col = sqrt(count) * 2;
            //cout << "block nine " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box nine works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            col = sqrt(count) * 3;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            col = sqrt(count) * 4;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
    }
    if (row >= sqrt(count) * 3 && row < sqrt(count) * 4)
    {
        row = sqrt(count) * 3;
        if (col < sqrt(count))
        {
            col = 0;
            //cout << "block seven " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box seven works" << endl;
            return false;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            col = sqrt(count);
            //cout << "block eight " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box eight works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            col = sqrt(count) * 2;
            //cout << "block nine " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box nine works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            col = sqrt(count) * 3;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            col = sqrt(count) * 4;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
    }
    if (row >= sqrt(count) * 4 && row < sqrt(count) * 5)
    {
        row = sqrt(count) * 4;
        if (col < sqrt(count))
        {
            col = 0;
            //cout << "block seven " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box seven works" << endl;
            return false;
        }
        if (col >= sqrt(count) && col < sqrt(count) * 2)
        {
            col = sqrt(count);
            //cout << "block eight " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box eight works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 2 && col < sqrt(count) * 3)
        {
            col = sqrt(count) * 2;
            //cout << "block nine " << count << endl;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box nine works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 3 && col < sqrt(count) * 4)
        {
            col = sqrt(count) * 3;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
        if (col >= sqrt(count) * 4 && col < sqrt(count) * 5)
        {
            col = sqrt(count) * 4;
            //cout << "block three " << count << endl;
            for (int r = 0; r < sqrt(count); r++)
            {
                for (int c = 0; c < sqrt(count); c++)
                {
                    if (sgrid[row + r][col + c] == num)
                    {
                        return true;
                    }
                }
            }
            //cout << "Box three works" << endl;
            return false;
        }
    }
}