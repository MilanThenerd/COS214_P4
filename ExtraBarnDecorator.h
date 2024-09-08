#ifndef BARNDECORATOR_H
#define BARNDECORATOR_H

#include "FarmUnitDecorator.h"
#include "Barn.h"

class ExtraBarnDecorator : public FarmUnitDecorator
{
private:
  Barn *barn;

public:
  ExtraBarnDecorator(FarmUnit *unit);
  int getTotalCapacity() const override;
  std::string getCropType() const override;
  std::string getSoilStateName() const;
  void increaseProduction();
  void harvest();
  int getLeftoverCapacity() const override;
  void notify();
  void addCrops(int cropAmount) override;
  int removeCrops(int cropAmount) override;
  void rain();
  FarmUnit *getWrappedUnit() { return decoratedUnit; }
  ~ExtraBarnDecorator();
};
#endif