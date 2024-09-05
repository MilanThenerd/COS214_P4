#include "FarmTraversal.h"

#include<iostream>

FarmTraversal::FarmTraversal(std::vector<std::vector<FarmUnit*>>& farmMap, int startX, int startY, bool type)
    : farmMap(farmMap), startX(startX), startY(startY), type(type), currentIndex(0)
{
  this->type = type;
  initialize();
}

void FarmTraversal::initialize() 
{
    visited.clear();
    path.clear();
    
    if (type == true) 
    {
        bfsTraversal();
    } 
    else
    {
        dfsTraversal();
    }
}

void FarmTraversal::insert(int x, int y, FarmUnit* unit) 
{
    if (isWithinBounds(x, y))
    {
      if(!contains(x,y))
      {
        length++;
      }
      farmMap[x][y] = unit;; 
    } 
    this->initialize();
}

bool FarmTraversal::contains(int x , int y) const
{
  if(farmMap[x][y] != nullptr)
  {
    return true;
  }
  return false;
}

FarmUnit* FarmTraversal::get(int x , int y)
{
  if (isWithinBounds(x, y))
  {
    return farmMap[x][y];
  }
  return nullptr;
}

void FarmTraversal::bfsTraversal() 
{
  if (!isWithinBounds(startX, startY)) return;
    
  bfsQueue.push({startX, startY});
  visited.insert({startX, startY});
    
  while (!bfsQueue.empty()) 
  {
    Coords current = bfsQueue.front();
    bfsQueue.pop();
    path.push_back(current);

    std::vector<Coords> neighbors = {{current.x+1, current.y}, {current.x-1, current.y}, {current.x, current.y+1}, {current.x, current.y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        bfsQueue.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}

void FarmTraversal::dfsTraversal()
{
  if (!isWithinBounds(startX, startY)) 
  {
    return;
  }
  dfsStack.push({startX, startY});
  visited.insert({startX, startY});

  while (!dfsStack.empty()) 
  {
    Coords current = dfsStack.top();
    dfsStack.pop();
    path.push_back(current);

    std::vector<Coords> neighbors = {{current.x+1, current.y}, {current.x-1, current.y}, {current.x, current.y+1}, {current.x, current.y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        dfsStack.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}

bool FarmTraversal::isWithinBounds(int x, int y) const 
{
  return x >= 0 && x < farmMap.size() && y >= 0 && y < farmMap[0].size();
}

FarmUnit* FarmTraversal::firstFarm() 
{
  currentIndex = 0;
  return isDone() ? nullptr : farmMap[path[currentIndex].x][path[currentIndex].y];
}

FarmUnit* FarmTraversal::currentFarm() 
{
  return isDone() ? nullptr : farmMap[path[currentIndex].x][path[currentIndex].y];
}

FarmUnit* FarmTraversal::next() 
{
  if (isDone()) return nullptr;
  currentIndex++;
  return isDone() ? nullptr : farmMap[path[currentIndex].x][path[currentIndex].y];
}

bool FarmTraversal::isDone() const 
{
    return currentIndex >= path.size();
}

bool FarmTraversal::hasNext() const 
{
    return currentIndex < path.size();
}

int FarmTraversal::getIndex(FarmUnit* unit) const
{
  for (size_t i = 0; i < path.size(); ++i)
  {
    int x = path[i].x;
    int y = path[i].y;
    if (farmMap[x][y] == unit)
    {
      return i;
    }
  }
  return -1;
}