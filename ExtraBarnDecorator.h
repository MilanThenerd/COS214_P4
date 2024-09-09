#ifndef BARNDECORATOR_H
#define BARNDECORATOR_H

#include "FarmUnitDecorator.h"

class ExtraBarnDecorator : public FarmUnitDecorator
{
private:
  FarmUnit *unit;

public:
  ExtraBarnDecorator(FarmUnit *unit);
  int getTotalCapacity() const;
  std::string getCropType() const;
  std::string getSoilStateName() const;
  void increaseProduction();
  void harvest();
  int getLeftoverCapacity() const;
  void notify();
  void addCrops(int cropAmount);
  int removeCrops(int cropAmount);
  void rain();
  FarmUnit *getWrappedUnit() { return unit; }
  ~ExtraBarnDecorator();
};
#endif