#ifndef BARN_H
#define BARN_H
#include "FarmTraversalBFS.h"
#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include <iostream>
#include "DecoratorHelper.h"

class Game;

class Barn : public FarmUnit
{
private:
  Coords coords;
  FarmTraversal *iterator;
  std::vector<FarmUnit*> surroundingUnits;
  std::vector<std::vector<FarmUnit *>> &farmMap;
  void setup();

public:
  Barn(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);
  int getTotalCapacity() const override;
  int getLeftoverCapacity() const override;
  std::string getCropType() const override;
  void addCrops(int cropAmount) override;
  int removeCrops(int cropAmount) override;
  std::vector<FarmUnit*> getNeighbours();
  void addNeighbour(FarmUnit* unit);
  void handleNeighbours();
};
#endif