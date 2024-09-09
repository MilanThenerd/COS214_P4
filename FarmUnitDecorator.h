#ifndef FARMUNITDECORATOR_H
#define FARMUNITDECORATOR_H

#include "FarmUnit.h"

class FarmUnitDecorator : public FarmUnit
{
protected:
  FarmUnit *unit;

public:
  FarmUnitDecorator(FarmUnit *unit) : unit(unit) {};
  virtual ~FarmUnitDecorator() = default;
  virtual int getTotalCapacity() const = 0;
  virtual int getLeftoverCapacity() const = 0;
  virtual std::string getCropType() const = 0;
  virtual void addCrops(int cropAmount) = 0;
  virtual int removeCrops(int cropAmount) = 0;
};
#endif