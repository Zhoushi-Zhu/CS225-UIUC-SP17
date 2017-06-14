/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include "png.h"
#include "dsets.h"

using namespace std;

class SquareMaze{
 public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  vector<int> solveMaze();
  PNG* drawMaze()const;
  PNG* drawMazeWithSolution();

 private:
  //vector<int> upwalls;
  vector<bool> downwalls;
  //vector<int> leftwalls;
  vector<bool> rightwalls;
  
  int width;
  int height;
};

#endif
