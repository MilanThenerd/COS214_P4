#include "FarmTraversal.h"

#include<iostream>

FarmTraversal::FarmTraversal(std::vector<std::vector<FarmUnit*>>& farmMap, int startX, int startY)
    : farmMap(farmMap), startX(startX), startY(startY), currentIndex(0)
{
}

void FarmTraversal::initialize() 
{
    visited.clear();
    path.clear();
}

void FarmTraversal::insert(int x, int y, FarmUnit* unit) 
{
    if (isWithinBounds(x, y))
    {
      farmMap[x][y] = unit;
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

bool FarmTraversal::isWithinBounds(int x, int y) const 
{
  return x >= 0 && x < (int)farmMap.size() && y >= 0 && y < (int)farmMap[0].size();
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

int FarmTraversal::getLength() const
{
  return farmMap.size() * farmMap[0].size();
}

int FarmTraversal::getCurrentIndex() const
{
  return currentIndex;
}

std::vector<Coords> FarmTraversal::getPath() const
{
  return path;
}

std::vector<std::vector<FarmUnit*>> FarmTraversal::getMap()
{
  return farmMap;
}

FarmUnit* FarmTraversal::getFarmUnitByIndex(int index)
{
    int numRows = farmMap.size();
    int numCols = farmMap[0].size();

    if (index < 0 || index >= numRows * numCols)
    {
        return nullptr;
    }
    int row = index / numCols;
    int col = index % numCols;

    return farmMap[row][col];
}