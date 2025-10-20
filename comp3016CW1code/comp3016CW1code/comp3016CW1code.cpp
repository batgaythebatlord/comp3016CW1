// comp3016CW1code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//░░░

#include <iostream>
#include <string>
#include "mazeHeader.cpp"

using namespace std;

//function declaration space
class Maze;
static void drawGrid(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist]);
string draw(bool stuff);
string drawObject(bool object);
void placeObjects(bool(&theCells)[yDist][xDist]);
void startMaze(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist]);
void carveMaze(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist], int xValue, int yValue);
static bool isEdge(bool(&theGrid)[yDist][xDist][4], int xValue, int yValue, int wall);
static bool isVisited(bool(&theCells)[yDist][xDist], int xValue, int yValue, int wall);
static void huntPhase(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist]);

class Maze
{
public:
    bool theGrid[yDist][xDist][4];
    bool theCells[yDist][xDist];
    Maze()
    {
        startMaze(theGrid, theCells);
    }

private:
    void startMaze(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist])
    {
        for (int i = 0; i < sizeof(theGrid) / sizeof(theGrid[0]); i++)
        {
            for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    theGrid[i][j][k] = false;
                }
            }
        }

        for (int i = 0; i < sizeof(theCells) / sizeof(theCells[0]); i++)
        {
            for (int j = 0; j < sizeof(theCells[0]) / sizeof(theCells[0][0]); j++)
            {
                theCells[i][j] = false;
            }
        }

        int yValue = rand() % sizeof(theGrid) / sizeof(theGrid[0]);
        int xValue = rand() % sizeof(theGrid[0]) / sizeof(theGrid[0][0]);
        theCells[yValue][xValue] = true;

        /*std::cout << "started!\n";
        std::cout << xValue << " " << yValue << "\n";*/

        carveMaze(theGrid, theCells, xValue, yValue);
    }

    void carveMaze(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist], int xValue, int yValue)
    {
        /*std::cout << "carve maze\n";*/

        bool wallcheck[4];
        int count = 0;


        for (int wall = 0; wall < 4; wall++)
        {
            if (isEdge(theGrid, xValue, yValue, wall) == false)
            {
                if (isVisited(theCells, xValue, yValue, wall) == false)
                {
                    wallcheck[wall] = false;
                    count++;
                }
                else
                {
                    wallcheck[wall] = true;
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

            theCells[yValue][xValue] = true;
            /*drawGrid(theGrid);*/


            carveMaze(theGrid, theCells, xValue, yValue);
        }
    }
    bool isEdge(bool(&theGrid)[yDist][xDist][4], int xValue, int yValue, int wall)
    {
        if (wall == 0 && yValue == 0) return true;
        if (wall == 1 && xValue == 0) return true;
        if (wall == 2 && yValue == sizeof(theGrid) / sizeof(theGrid[0]) - 1) return true;
        if (wall == 3 && xValue == sizeof(theGrid[0]) / sizeof(theGrid[0][0]) - 1) return true;
        return false;
    }
    bool isVisited(bool(&theCells)[yDist][xDist], int xValue, int yValue, int wall)
    {
        if (wall == 0) return theCells[yValue - 1][xValue];
        if (wall == 1) return theCells[yValue][xValue - 1];
        if (wall == 2) return theCells[yValue + 1][xValue];
        if (wall == 3) return theCells[yValue][xValue + 1];
        return false;
    }

    void huntPhase(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist])
    {
        /*std::cout << "hunt phase\n";*/

        int xValue = 0;
        int yValue = 0;
        int count = 0;
        bool found = false;

        do
        {
            if (theCells[yValue][xValue] == true)
            {
                for (int wall = 0; wall < 4; wall++)
                {
                    if (isEdge(theGrid, xValue, yValue, wall) == false)
                    {
                        if (isVisited(theCells, xValue, yValue, wall) == false)
                        {
                            found = true;
                            /*std::cout << xValue << " " << yValue << "\n";*/
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
            theGrid[0][0][1] = true;
            theGrid[sizeof(theGrid) / sizeof(theGrid[0]) - 1][sizeof(theGrid[0]) / sizeof(theGrid[0][0]) - 1][3] = true;
            placeObjects(theCells);
            drawGrid(theGrid, theCells);
        }
    }

    void placeObjects(bool(&theCells)[yDist][xDist])
    {
        int count = 0;
        do
        {
            int yValue = rand() % sizeof(theCells) / sizeof(theCells[0]);
            int xValue = rand() % sizeof(theCells[0]) / sizeof(theCells[0][0]);
            if (theCells[yValue][xValue] == true)
            {
                theCells[yValue][xValue] = false;
                count++;
            }
        } while (count <= 15);
    }
};

int main()
{
    srand(time(NULL));
    
    Maze level1;
}

static void drawGrid(bool (&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist])
{
    for (int i = 0; i < sizeof(theGrid) / sizeof(theGrid[0]); i++)
    {
        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            std::cout << "|||" + draw(theGrid[i][j][0]) + "|||";
        }

        std::cout << "\n";

        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            //std::cout << draw(theGrid[i][j][1]) << i << j << draw(theGrid[i][j][3]);
            std::cout << draw(theGrid[i][j][1]) + drawObject(theCells[i][j]) + draw(theGrid[i][j][3]);
            // the numbers go ANTICLOCKWISE!!!!!!
        }

        std::cout << "\n";

        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            std::cout << "|||" + draw(theGrid[i][j][2]) + "|||";
        }

        std::cout << "\n";
    }

    std::cout << "\n";
}

string draw(bool stuff)
{
    if (stuff) return "   ";
    return "|||";
}

string drawObject(bool object)
{
    if (object) return "   ";
    return " 0 ";
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
