#include "Truck.h"

#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <map>
#include <iostream>

Truck::Truck(std::vector<std::vector<FarmUnit *>> &map, int capacity) : farmMap(map), capacity(capacity)
{
  this->farmIterator = new FarmTraversalBFS(map, 0, 0);
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

bool Truck::callTruck(FarmUnit *unit)
{
  if ((int)farmVector.size() < capacity)
  {
    this->farmVector.push_back(unit);
    return true;
  }
  return false;
}

std::vector<Coords> Truck::getPath() const
{
  return this->path;
}

void Truck::findShortestPath()
{
  std::vector<Coords> path;
  for (const auto &unit : farmVector)
  {
    Coords coords = getCoords(unit);
    path.push_back(coords);
  }
  this->path = path;
}

Coords Truck::getCoords(FarmUnit *unit)
{
  Coords coord(-1, -1);
  for (size_t i = 0; i < farmMap.size(); ++i)
  {
    for (size_t j = 0; j < farmMap[i].size(); ++j)
    {
      if (unit == farmMap[i][j])
      {
        return Coords(j, i);
      }
    }
  }
  return coord;
}

Coords *Truck::getPosition()
{
  return this->currentPosition;
}

bool Truck::moveTowardsNextFarmUnit(int speed)
{
  if (path.empty())
  {
    return false;
  }
  Coords nextPosition = path.front();
  if (currentPosition->x != nextPosition.x)
  {
    if (currentPosition->x < nextPosition.x)
    {
      currentPosition->x++;
    }
    else
    {
      currentPosition->x--;
    }
  }
  else if (currentPosition->y != nextPosition.y)
  {
    if (currentPosition->y < nextPosition.y)
    {
      currentPosition->y++;
    }
    else
    {
      currentPosition->y--;
    }
  }
  if (currentPosition->x == nextPosition.x && currentPosition->y == nextPosition.y)
  {
    path.erase(path.begin());
    return true;
  }
  return false;
}