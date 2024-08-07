/*
You shouldn't touch this file. You have all you need in the functions introduced in "main.cpp".
*/

#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <stdexcept>

using namespace std;

// Maze building block (cell)
struct Point
{
    size_t row;
    size_t col;
};

namespace __privates
{
    // Map
    const size_t mapSize = 11;  // Map size in cells
    bool map[mapSize][mapSize]; // Map grid (isWalkable)

    // Sets every cell to walkable
    void clear()
    {
        for (size_t row = 0; row < mapSize; row++)
        {
            for (size_t col = 0; col < mapSize; col++)
                map[row][col] = true;
        }
    }

    // Player
    Point playerPos; // Player position

    // Goal
    Point goalPos; // Goal position
};

// Initalizes maze with level file
bool initMaze(const string &levelFile)
{
    __privates::clear();

    ifstream file(levelFile.c_str());
    if (file.is_open())
    {
        string line;
        for (size_t row = 0; row < __privates::mapSize; row++)
        {
            getline(file, line);
            for (size_t col = 0; col < __privates::mapSize; col++)
            {
                if (line[col] == '>')
                {
                    __privates::playerPos.row = row;
                    __privates::playerPos.col = col;
                }
                else if (line[col] == '$')
                {
                    __privates::goalPos.row = row;
                    __privates::goalPos.col = col;
                }
                __privates::map[row][col] = (line[col] != '#');
            }
        }
        file.close();
    }
    else
        throw new invalid_argument("Level file was not found.");
}

// Map

// Checks if cell around player is walkable (right: [-1 0 1], down: [-1 0 1])
bool isWalkable(int right, int down)
{
    int row = __privates::playerPos.row + min(max(down, -1), 1);
    int col = __privates::playerPos.col + min(max(right, -1), 1);
    if (row < 0 || row >= __privates::mapSize || col < 0 || col >= __privates::mapSize)
        return false;
    return __privates::map[row][col];
}

// Prints maze as a whole
void printMaze()
{
    for (size_t row = 0; row < __privates::mapSize; row++)
    {
        for (size_t col = 0; col < __privates::mapSize; col++)
        {
            if (__privates::playerPos.row == row && __privates::playerPos.col == col)
            {
                cout << ">";
            }
            else if (__privates::goalPos.row == row && __privates::goalPos.col == col)
            {
                cout << "$";
            }
            else
            {
                cout << (__privates::map[row][col] ? "." : "#");
            }
        }
        cout << endl;
    }
}

// Prints part of maze around the player
void printAround()
{
    for (int down = -1; down <= 1; down++)
    {
        for (int right = -1; right <= 1; right++)
        {

            if (down == 0 && right == 0)
            {
                cout << ">";
            }
            else if (__privates::goalPos.row == __privates::playerPos.row + down && __privates::goalPos.col == __privates::playerPos.col + right)
            {
                cout << "$";
            }
            else
            {
                cout << (isWalkable(down, right) ? "." : "#");
            }
        }
        cout << endl;
    }
}

// Player

// Gets player poision in maze
Point getPlayerPos() { return __privates::playerPos; }

// Moves player one step (right: [-1 0 1], down: [-1 0 1])
void movePlayer(int right, int down)
{
    int row = __privates::playerPos.row + min(max(down, -1), 1);
    int col = __privates::playerPos.col + min(max(right, -1), 1);
    if (row < 0 || row >= __privates::mapSize || col < 0 || col >= __privates::mapSize || !__privates::map[row][col])
        return;
    __privates::playerPos.row = row;
    __privates::playerPos.col = col;
}

// Goal

// Gets goal poision in maze
Point getGoalPos() { return __privates::goalPos; }

// Check if reached goal
bool hasReachedGoal()
{
    return __privates::playerPos.row == __privates::goalPos.row &&
           __privates::playerPos.col == __privates::goalPos.col;
}

#endif
