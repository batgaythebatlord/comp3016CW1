// comp3016CW1code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//░░░

#include <iostream>
#include <string>
#include "mazeHeader.cpp"

using namespace std;

static void drawGrid(bool(&theGrid)[xDist][yDist][4]);
string draw(bool stuff);

int main()
{
    bool grid[yDist][xDist][4];
    bool cellsNotVisited[yDist][xDist];

    drawGrid(grid);
}

static void drawGrid(bool (&theGrid)[xDist][yDist][4])
{
    for (int i = 0; i < sizeof(theGrid) / sizeof(theGrid[0]); i++)
    {
        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            cout << "||||" + draw(theGrid[i][j][0]) + "||||";
        }

        cout << "\n";

        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            cout << draw(theGrid[i][j][1]) + "    " + draw(theGrid[i][j][3]);
            // the numbers go ANTICLOCKWISE!!!!!!
        }

        cout << "\n";

        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            cout << "||||" + draw(theGrid[i][j][2]) + "||||";
        }

        cout << "\n";
    }

    cout << "\n";
}


string draw(bool stuff)
{
    if (!stuff) return "    ";
    return "||||";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
