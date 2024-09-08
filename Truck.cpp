#include "Truck.h"

#include <cmath>
#include <algorithm>

#include <unordered_map>
#include <iostream>

Truck::Truck(std::vector<std::vector<FarmUnit*>>& map , int capacity) : farmMap(map) , capacity(capacity)
{
  this->farmIterator = new FarmTraversalBFS(map,0,0);

  int maxRows = farmMap.size();
  int maxCols = farmMap[0].size();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distX(-5, maxRows + 5);
  std::uniform_int_distribution<> distY(-5, maxCols + 5);
  int randomX = distX(gen);
  int randomY = distY(gen);
  currentPosition = new Coords(randomX, randomY);
}

bool Truck::callTruck(FarmUnit* unit)
{
  if((int)farmVector.size() == capacity)
  {
    return false;
  }
  this->farmVector.push_back(unit);
  return true;
}

std::vector<Coords> Truck::getPath() const
{
  return this->path;
}

void Truck::findShortestPath()
{
   this->path = findShortestPathRec();
}

double Truck::computeDistance(const Coords& a, const Coords& b) 
{
    return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

Coords Truck::getCoords(FarmUnit* unit)
{
  Coords coord(-1,-1);
  for(int i = 0 ; i < (int)farmMap.size() ; i++)
  {
    for(int j = 0 ; j < (int)farmMap[i].size() ; j++)
    {
      if(unit == farmMap[i][j])
      {
        return Coords(i,j);
      }
    }
  }
  return coord;
}

std::vector<Coords> Truck::findShortestPathRec() 
{
  std::vector<Coords> path;
  if (farmVector.empty()) 
  {
    return path;
  }
  
  int x = getCoords(farmVector.front()).x;
  int y = getCoords(farmVector.front()).y;
  Coords start(x,y);

  path.push_back(start);
  std::vector<Coords> unvisited;
  for (const auto& unit : farmVector) 
  {
    x = getCoords(unit).x;
    y = getCoords(unit).y;
    Coords coords(x,y);
    unvisited.push_back(coords);
  }
  unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), start), unvisited.end());
  while (!unvisited.empty()) 
  {
    Coords current = path.back();
    double minDistance = std::numeric_limits<double>::max();
    Coords nextPoint(-1,-1);
    auto nearestIt = unvisited.end();
    for (auto it = unvisited.begin(); it != unvisited.end(); ++it) 
    {
      double distance = computeDistance(current, *it);
      if (distance < minDistance) 
      {
        minDistance = distance;
        nextPoint = *it;
        nearestIt = it;
      }
    }
    if (nearestIt != unvisited.end()) 
    {
      path.push_back(nextPoint);
      unvisited.erase(nearestIt);
    }
  }
  return path;
}

Coords* Truck::getPosition()
{
  return this->currentPosition;
}

void Truck::moveTowardsNextFarmUnit(int speed)
{
  if(path.empty())
  {
    return;
  }
  Coords nextPosition = path.front();
  if (currentPosition->x != nextPosition.x) 
  {
    if(currentPosition->x < nextPosition.x)
    {
      currentPosition->x += std::min(speed , nextPosition.x - currentPosition->x);
    }
    else
    {
      currentPosition->x -= std::min(speed , currentPosition->x - nextPosition.x);
    }
  }
  else if(currentPosition->y != nextPosition.y)
  {
    if(currentPosition->y < nextPosition.y)
    {
      currentPosition->y += std::min(speed , nextPosition.y - currentPosition->y);
    }
    else 
    {
      currentPosition->y -= std::min(speed , currentPosition->y - nextPosition.y);
    }
  }
  if (currentPosition->x == nextPosition.x && currentPosition->y == nextPosition.y) 
  {
    path.erase(path.begin());
  }
}