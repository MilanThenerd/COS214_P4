#ifndef EXTRABARNDECORATOR_H
#define EXTRABARNDECORATOR_H

#include "FarmUnitDecorator.h"
#include "CropField.h"

class ExtraBarnDecorator : public FarmUnitDecorator
{
private:
  FarmUnit *unit;

public:
  ExtraBarnDecorator(FarmUnit *unit);
  int getTotalCapacity() const;
  std::string getCropType() const;
  std::string getSoilStateName() const;
  void harvest();
  int getLeftoverCapacity() const;
  void notifyDelivery();
  void addCrops(int cropAmount);
  int removeCrops(int cropAmount);
  void rain();
  FarmUnit *getWrappedUnit() { return unit; }
  ~ExtraBarnDecorator();
};
#endif