#ifndef BARN_H
#define BARN_H
#include "FarmTraversalBFS.h"
#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include <iostream>
#include "DecoratorHelper.h"

// Game forward declaration
class Game;
// class Game
// {
// public:
//   static bool hasDecorator(FarmUnit *unit, const std::type_info &decoratorType);
// };

class Barn : public FarmUnit
{
private:
  Coords coords;
  FarmTraversal *iterator;
  std::vector<std::vector<FarmUnit *>> &farmMap;
  void setup();

public:
  Barn(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);
  int getTotalCapacity() const override;
  int getLeftoverCapacity() const override;
  std::string getCropType() const override;
  void addCrops(int cropAmount) override;
  int removeCrops(int cropAmount) override;
};
#endif