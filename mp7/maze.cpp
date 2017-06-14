/* Your code here! */
#include "maze.h"

using namespace std;

SquareMaze::SquareMaze(){
  width = 0;
  height = 0;
  
}

void SquareMaze::makeMaze(int width, int height){
  this->height = height;
  this->width = width;

  for(int i = 0; i < height*width; i++){
    //upwalls.push_back(1);
    downwalls.push_back(true);
    rightwalls.push_back(true);
    //leftwalls.push_back(1);
  }

  DisjointSets grid_set;
  grid_set.addelements(height*width);

  srand (time(NULL));
  
  bool breakright = rand()%2;
  int i = 0;
  while(i < width * height - 1){
    
    int breakx = rand() % (width);
    int breaky = rand() % (height);

    if(breakright){
      if(breakx < width - 1 && rightwalls[breaky * width + breakx] && (grid_set.find(breaky * width + breakx) != grid_set.find(breaky * width + breakx + 1))){
	     rightwalls[breaky * width + breakx] = false;
	     grid_set.setunion(breaky * width + breakx, breaky * width + (breakx + 1));
       i++;
      }
      breakright = !breakright;
    }
    else{
      if(breaky < height - 1 && downwalls[breaky * width + breakx] && (grid_set.find(breaky * width + breakx) != grid_set.find((breaky + 1) * width + breakx))){
	     downwalls[breaky * width + breakx] = false;
	     grid_set.setunion(breaky * width + breakx, (breaky + 1) * width + breakx);
       i++;
      }
      breakright = !breakright;
    }
    
  }

  //breakright = rand()%2;

  /*for(int i = 0; i < width ; i++){
    for(int j = 0; j < height; j++){
      int breakx = i;
      int breaky = j;
      //if(breakright == 1){
        if(breakx < width - 1 && rightwalls[breaky * width + breakx] && (grid_set.find(breaky * width + breakx) != grid_set.find(breaky * width + breakx + 1))){
	       rightwalls[breaky * width + breakx] = false;
	       grid_set.setunion(breaky * width + breakx, breaky * width + breakx + 1);
         i++;
      	}
	      if(breaky < height - 1 && downwalls[breaky * width + breakx] && (grid_set.find(breaky * width + breakx) != grid_set.find((breaky + 1) * width + breakx))){
	       downwalls[breaky * width + breakx] = false;
	       grid_set.setunion(breaky * width + breakx, (breaky + 1) * width + breakx);
         i++
	      }*/
        //breakright = !breakright;
      /*}else{
	      if(breaky < height - 1 && grid_set.find(breaky * width + breakx) != grid_set.find((breaky + 1) * width + breakx)){
	      downwalls[breaky * width + breakx] = 0;
	      grid_set.setunion(breaky * width + breakx, (breaky + 1) * width + breakx);
	      }
        if(breakx < width - 1 && grid_set.find(breaky * width + breakx) != grid_set.find(breaky * width + (breakx + 1))){
	       rightwalls[breaky * width + breakx] = 0;
	       grid_set.setunion(breaky * width + breakx, breaky * width + breakx + 1);
	      }
        breakright = !breakright;
      }*/
   // }
  //}
  
  
}

bool SquareMaze::canTravel(int x, int y, int dir)const{
  switch(dir){
  case(0):
    return !(rightwalls[y*width + x]);
    break;
    
  case(1):
    return !(downwalls[y*width + x]);
    break;

  case(2):
    if(x == 0)
      return false;
    else
      return !(rightwalls[y*width + x - 1]);
    break;
    
  case(3):
    if(y == 0)
      return false;
    else
      return !(downwalls[(y - 1)*width + x]);
    break;
  }

  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  switch(dir){
  case(0):
    rightwalls[y*width + x] = exists;
    break;
    
  case(1):
    downwalls[y*width + x] = exists;
    break;

    /* case(2):
    rightwalls[y*width + x - 1] = exists;
    break;
    
  case(3):
     downwalls[(y - 1)*width + x] = exists;
     break;*/
  }
}

vector<int> SquareMaze::solveMaze(){
  vector<int> ret;
  vector<int> target;
  queue<int> q;
  vector<int> visited;

  for(int i = 0; i < width*height; i++)
    visited.push_back(0);

  map<int, int> parent;

  q.push(0);
  visited[0] = 1;
  
  int count = 0;
  while(!q.empty()){
    int curr = q.front();
    q.pop();
    //cout<<++count<<" "<<curr%width<<" "<<curr/width<<endl;

    if(curr/width == height - 1){
      target.push_back(curr%width);
      //cout<<target.size()<<endl;
    }
    
    if(canTravel(curr%width, curr/width, 0) && visited[curr+1] == 0){
      q.push(curr+1);
      visited[curr+1] = 1;
      parent.insert(pair<int,int>(curr+1, curr));
      //cout<<"right"<<endl;
    }
    
    if(canTravel(curr%width, curr/width, 1) && visited[curr+width] == 0){
	q.push(curr+width);
	visited[curr+width] = 1;
	parent.insert(pair<int,int>(curr+width, curr));
	//cout<<"down"<<endl;
    }
    
    if(canTravel(curr%width, curr/width, 2) && visited[curr-1] == 0){
      q.push(curr-1);
      visited[curr-1] = 1;
      parent.insert(pair<int,int>(curr-1, curr));
     // cout<<"left"<<endl;
    }
    
    if(canTravel(curr%width, curr/width, 3) && visited[curr-width] == 0){
      q.push(curr-width);
      visited[curr-width] = 1;
      parent.insert(pair<int,int>(curr-width, curr));
      //cout<<"up"<<endl;
    }
  }

  //cout<<target.size()<<" "<<width<<endl;
  int targetX = target[width - 1];
  
  stack<int> temp;
  int sol = width * (height - 1) + targetX;

  while(sol != 0){
    int temp2 = parent[sol];
      if(sol - temp2 == -1)
	temp.push(2);
      else if(sol - temp2 == 1)
	temp.push(0);
      else if(sol - temp2 == width)
	temp.push(1);
      else 
	temp.push(3);

    sol = temp2;
  }

  while(!temp.empty()){
    ret.push_back(temp.top());
    temp.pop();
  }
  
  return ret;
}

PNG* SquareMaze::drawMaze()const{
  int w = width*10+1;
  int h = height*10+1;

  PNG* ret = new PNG (w, h);

  RGBAPixel black;
  black.red = 0;
  black.blue = 0;
  black.green = 0;
  
  RGBAPixel white;
  white.red = 255;
  white.blue = 255;
  white.green = 255;

  for(int i = 0; i < w; i++){
    *(*ret)(i,0) = black;
  }

  for(int i = 0; i < w; i++){
    *(*ret)(0,i) = black;
  }

    for(int i = 1; i < 10; i++){
    *(*ret)(i,0) = white;
  }

  for(int i = 0; i < width*height; i++){
    int tempX = i%width;
    int tempY = i/width;

    if(rightwalls[i] == 1)
      for(int k = 0; k < 11; k++)
	*(*ret)((tempX + 1) * 10, tempY * 10 + k) = black;
    
    if(downwalls[i] == 1)
      for(int k = 0; k < 11; k++)
	*(*ret)(tempX * 10 + k, (tempY + 1) * 10) = black;
      
  }

  return ret;
  
}


PNG* SquareMaze::drawMazeWithSolution(){
  PNG* ret = drawMaze();

  vector<int> sol = solveMaze();
  
  RGBAPixel red;
  red.red = 255;
  red.blue = 0;
  red.green = 0;
  
  *(*ret)(5,5) = red;

  int x = 5;
  int y = 5;

  int mazeX = 0;
  int mazeY = 0;

  for(size_t i = 0; i < sol.size(); i++){
    if(sol[i] == 0){
      mazeX++;
      for(int j = 0; j < 10; j++){
	*(*ret)(x,y) = red;
	x++;
      }
    }else if(sol[i] == 1){
      mazeY++;
      for(int j = 0; j < 10; j++){
	*(*ret)(x,y) = red;
	y++;
      }
    }else if(sol[i] == 2){
      mazeX--;
      for(int j = 0; j < 10; j++){
	*(*ret)(x,y) = red;
	x--;
      }
    }else if(sol[i] == 3){
      mazeY--;
      for(int j = 0; j < 10; j++){
	*(*ret)(x,y) = red;
	y--;
      }
    }
  }

  *(*ret)(x,y) = red;


  RGBAPixel white;
  white.red = 255;
  white.blue = 255;
  white.green = 255;

  for(int i = 1; i < 10; i++)
    *(*ret)(mazeX * 10 + i, (mazeY + 1) * 10) = white;
  
  return ret;
}
