#ifndef BARN_H
#define BARN_H
#include "FarmTraversalBFS.h"
#include "FarmUnit.h"

class Barn : public FarmUnit
{
private:
  FarmTraversal *iterator;

public:
  Barn(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);
  int getTotalCapacity() const override;
  int getLeftoverCapacity() const override;
  std::string getCropType() const override;
  void addCrops(int cropAmount) override;
  int removeCrops(int cropAmount) override;
};
#endif