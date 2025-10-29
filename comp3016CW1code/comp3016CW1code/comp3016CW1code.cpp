// comp3016CW1code.cpp : This file contains the 'main' function. Program execution begins and ends there.
//░░░

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

//variables
constexpr int xDist = 22;
constexpr int yDist = 16;
bool gameOver;

//function declaration space
class Maze;
bool finished(int yPos, int xPos, bool(&theCells)[yDist][xDist]);
static void drawGrid(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist], float timer, int(&playerLoc)[2]);
string draw(bool stuff);
string drawObject(bool object);
void keyPressed(int(&playerLoc)[2], bool(&theGrid)[yDist][xDist][4]);

//in the class
void startMaze(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist]);
void carveMaze(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist], int xValue, int yValue);
static bool isEdge(bool(&theGrid)[yDist][xDist][4], int xValue, int yValue, int wall);
static bool isVisited(bool(&theCells)[yDist][xDist], int xValue, int yValue, int wall);
static void huntPhase(bool(&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist]);
void placeObjects(bool(&theCells)[yDist][xDist]);


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
    ::SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    srand(time(NULL));
    float timer = 00.00;
    int playerPos[2];
    gameOver = false;


    if (_kbhit())
    {
        cout << "_kbhit";
    }

    playerPos[0] = 0;
    playerPos[1] = 0;
    int yPos;
    int xPos;
    Maze level;
    do
    {
        drawGrid(level.theGrid, level.theCells, timer, playerPos);
        keyPressed(playerPos, level.theGrid);
        yPos = playerPos[0];
        xPos = playerPos[1];
        Sleep(100);
    } while (!finished(yPos, xPos, level.theCells));
    drawGrid(level.theGrid, level.theCells, timer, playerPos);
}

bool finished(int yPos, int xPos, bool(&theCells)[yDist][xDist])
{
    bool areWeFinsihed = false;

    if (yPos >= (yDist-1) && xPos >= (xDist-1))
    {
        areWeFinsihed = true;
    }

    for (int i = 0; i < sizeof(theCells) / sizeof(theCells[0]); i++)
    {
        for (int j = 0; j < sizeof(theCells[0]) / sizeof(theCells[0][0]); j++)
        {
            if (theCells[i][j] == false)
            {
                areWeFinsihed = false;
            }
        }
    }

    return areWeFinsihed;
}

static void drawGrid(bool (&theGrid)[yDist][xDist][4], bool(&theCells)[yDist][xDist], float timer, int(&playerLoc)[2])
{
    for (int i = 0; i < sizeof(theGrid) / sizeof(theGrid[0]); i++)
    {
        std::cout << "\n";
        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            std::cout << "|||" + draw(theGrid[i][j][0]) + "|||";
        }

        std::cout << "\n";

        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            //std::cout << draw(theGrid[i][j][1]) << i << j << draw(theGrid[i][j][3]);
            if (i == playerLoc[0] && j == playerLoc[1])
            {
                std::cout << draw(theGrid[i][j][1]) + " + " + draw(theGrid[i][j][3]);
                theCells[i][j] = true;
            }
            else
            {
                std::cout << draw(theGrid[i][j][1]) + drawObject(theCells[i][j]) + draw(theGrid[i][j][3]);
            }
            // the numbers go ANTICLOCKWISE!!!!!!
        }

        std::cout << "\n";

        for (int j = 0; j < sizeof(theGrid[0]) / sizeof(theGrid[0][0]); j++)
        {
            std::cout << "|||" + draw(theGrid[i][j][2]) + "|||";
        }

        
    }

    std::cout << "    " << timer << "\n";
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

void keyPressed(int(&playerLoc)[2], bool(&theGrid)[yDist][xDist][4])
{
    if(_kbhit())
    {
        int yPos = playerLoc[0];
        int xPos = playerLoc[1];

        switch (_getch()) {
        case KEY_UP:
            //cout << endl << "Up" << endl;//key up
            if (yPos != 0 && theGrid[yPos][xPos][0] == true)
            {
                playerLoc[0]--;
            }
            break;
        case KEY_DOWN:
            //cout << endl << "Down" << endl;   // key down
            if (yPos != yDist && theGrid[yPos][xPos][2] == true)
            {
                playerLoc[0]++;
            }
            break;
        case KEY_LEFT:
            //cout << endl << "Left" << endl;  // key left
            if (xPos != 0 && theGrid[yPos][xPos][1] == true)
            {
                playerLoc[1]--;
            }
            break;
        case KEY_RIGHT:
            //cout << endl << "Right" << endl;  // key right
            if (xPos != xDist && theGrid[yPos][xPos][3] == true)
            {
                playerLoc[1]++;
            }
            break;
        default:
            break;
        }
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
