#ifndef TRUCK_H
#define TRUCK_H

#include "FarmUnit.h"
#include "Coords.h"
#include "FarmTraversalBFS.h"

#include <queue>
#include <cmath>
#include <random>

class Truck
{
  protected:
    int capacity;
    std::vector<FarmUnit*> farmVector;
    std::vector<std::vector<FarmUnit*>> farmMap;
    std::vector<Coords> path;
    FarmTraversalBFS* farmIterator;
    void findShortestPath();
    Coords getCoords(FarmUnit* unit);
    Coords* currentPosition;
  public:
    Truck(std::vector<std::vector<FarmUnit*>>& map , int capacity);
    virtual ~Truck() {} 
    bool callTruck(FarmUnit* unit);
    virtual void startEngine() = 0;
    virtual Truck* clone() const = 0;
    std::vector<Coords> getPath() const;
    FarmUnit* getNextFarmUnit() const;
    void moveTowardsNextFarmUnit(int speed);
    Coords* getPosition();
};
#endif