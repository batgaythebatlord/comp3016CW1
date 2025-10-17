// comp3016CW1code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//░░░

#include <iostream>
#include <string>
#include "mazeHeader.cpp"

using namespace std;

//function declaration space
static void drawGrid(bool(&theGrid)[xDist][yDist][4]);
string draw(bool stuff);
void startMaze(bool(&theGrid)[xDist][yDist][4], bool(&theCells)[xDist][yDist]);
void carveMaze(bool(&theGrid)[xDist][yDist][4], bool(&theCells)[xDist][yDist], int xValue, int yValue);
static bool isEdge(bool(&theGrid)[xDist][yDist][4], int xValue, int yValue, int wall);
static void huntPhase(bool(&theGrid)[xDist][yDist][4], bool(&theCells)[xDist][yDist]);


int main()
{
    bool grid[yDist][xDist][4];
    bool cellsNotVisited[yDist][xDist];

    startMaze(grid, cellsNotVisited);
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

void startMaze(bool(&theGrid)[xDist][yDist][4], bool(&theCells)[xDist][yDist])
{
    int yValue = rand() % sizeof(theGrid) / sizeof(theGrid[0]);
    int xValue = rand() % sizeof(theGrid[0]) / sizeof(theGrid[0][0]);
    theCells[yValue][xValue] = false;

    cout << "started!\n";

    carveMaze(theGrid, theCells, xValue, yValue);
}

void carveMaze(bool(&theGrid)[xDist][yDist][4], bool(&theCells)[xDist][yDist], int xValue, int yValue)
{

    bool wallcheck[4];
    int count = 0;


    for (int wall = 0; wall < 4; wall++)
    {
        if (isEdge(theGrid, xValue, yValue, wall) == false)
        {
            if (isUnvisited(theCells, xValue, yValue, wall) == true)
            {
                wallcheck[wall] = true;
                count++;
            }
            else
            {
                wallcheck[wall] = false;
            }
        }
        else
        {
            wallcheck[wall] = true;
        }
    }


    if (count == 0)
    {
        huntPhase(theGrid, theCells);
    }
    else
    {
        int wallPicked = -1;
        do
        {
            wallPicked = rand() % 4;
        } while (wallcheck[wallPicked] == true);

        cout << wallPicked + " wall picked";

        theGrid[yValue][xValue][wallPicked] = true;
        switch (wallPicked)
        {
        case 0:
            yValue--;
            theGrid[yValue][xValue][2] = true;
            break;
        case 1:
            xValue--;
            theGrid[yValue][xValue][3] = true;
            break;
        case 2:
            yValue++;
            theGrid[yValue][xValue][0] = true;
            break;
        case 3:
            xValue++;
            theGrid[yValue][xValue][1] = true;
            break;
        default:
            break;
        }

        theCells[yValue][xValue] = false;
        drawGrid(theGrid);


        carveMaze(theGrid, theCells, xValue, yValue);
    }
}
static bool isEdge(bool(&theGrid)[xDist][yDist][4], int xValue, int yValue, int wall)
{
    if (wall == 0 && yValue == 0) return true;
    if (wall == 1 && xValue == 0) return true;
    if (wall == 2 && yValue == sizeof(theGrid) / sizeof(theGrid[0]) - 1) return true;
    if (wall == 3 && xValue == sizeof(theGrid[0]) / sizeof(theGrid[0][0]) - 1) return true;
    return false;
}
static bool isUnvisited(bool(&theCells)[xDist][yDist], int xValue, int yValue, int wall)
{
    if (wall == 0) return theCells[yValue - 1][xValue];
    if (wall == 1) return theCells[yValue][xValue - 1];
    if (wall == 2) return theCells[yValue + 1][xValue];
    if (wall == 3) return theCells[yValue][xValue + 1];
    return true;
}

static void huntPhase(bool(&theGrid)[xDist][yDist][4], bool(&theCells)[xDist][yDist])
{

    int xValue = 0;
    int yValue = 0;
    int count = 0;
    bool found = false;

    do
    {
        if (theCells[yValue][xValue] == false)
        {
            for (int wall = 0; wall < 4; wall++)
            {
                if (isEdge(theGrid, xValue, yValue, wall) == false)
                {
                    if (isUnvisited(theCells, xValue, yValue, wall) == true)
                    {
                        found = true;
                    }
                }
            }
        }

        if (found == false)
        {
            if (xValue != sizeof(theGrid[0]) / sizeof(theGrid[0][0]) - 1)
            {
                xValue++;
            }
            else if (yValue != sizeof(theGrid) / sizeof(theGrid[0]) - 1)
            {
                xValue = 0;
                yValue++;
            }
        }
        count++;
    } while (found == false && count <= sizeof(theGrid[0]) / sizeof(theGrid[0][0]) * sizeof(theGrid) / sizeof(theGrid[0]));

    if (found) carveMaze(theGrid, theCells, xValue, yValue);


    else
    {
        drawGrid(theGrid);
        cout << "done :)";
    }
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
