/*
The goal of this task is to develop an algorithm to solve a maze (reach a goal) without knowing
the maze as a whole from the get-go, you will need to explore the maze step by step.

You have to include "maze.h".

Your code goes in the *initialize* and *solve* functions. Read the instructions there carefully.

Compile your code using any c++ compiler and pass level filename as an argument, for example:
g++ main.cpp -o main.exe
main.exe level1.txt
*/
 /*
    This function will keep running forever until the goal is reached.

    You can access the maze API through below functions.

    Sense and Control:
        isWalkable(right, down): checks if cell around player is walkable (right: [-1 0 1], down: [-1 0 1])
        movePlayer(right, down): moves player one step (right: [-1 0 1], down: [-1 0 1])

    Global Info:
        getPlayerPos(): gets player position in maze
        getGoalPos()  : gets goal position in maze

    Debugging:
        printMaze()  : prints maze as a whole
        printAround(): prints part of maze around player
    */
#include "maze.h"
#include <stack>
#include <map>
using namespace std;

stack<pair<int,int>> road;
map<pair<int,int>,bool> visited;
int xdir[] = {1,1,0,1,0,-1,-1,-1};
int ydir[] = {1,0,1,-1,-1,1,0,-1};
void backTrack(){
    if(road.empty())
        return;
    pair<int,int> move = road.top();
    movePlayer(-move.first,-move.second);
    road.pop();
}
void printInfo(){
    cout << "your position is: "<< getPlayerPos().col<< "," << getPlayerPos().row << endl;
    printMaze();
    printAround();
    cout << "goal position is: "<< getGoalPos().col<< "," << getGoalPos().row << endl;
}
void initialize()
{


}
// solution based on iterative dfs
void solve()
{
   for(int i = 0 ;i< 8;i++){
    pair<int,int> pos = {getPlayerPos().col,getPlayerPos().row};

    if(isWalkable(xdir[i],ydir[i]) && !visited[{pos.first+xdir[i],pos.second+ydir[i]}]){
        road.push({xdir[i],ydir[i]});
        visited[{pos.first+xdir[i],pos.second+ydir[i]}] = true;
        movePlayer(xdir[i],ydir[i]);
        // printInfo();
        return;
    }
   }
   backTrack();
}

int main(int argc, char const *argv[])
{
    // Initalize level
    const string &levelFile = "level5.txt";
    initMaze(levelFile);

    initialize();
    int t  =100;
    // Game loop
    while (t--)
    {
        // Check reached goal
        if (hasReachedGoal())
        {
            // Hurray!
            cout << "Reached Goal!" << endl;
            break;
        }

        // Solve maze
        solve();
    }

    return 0;
}
