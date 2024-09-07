#ifndef CROPFIELD_H
#define CROPFIELD_H

#include "FarmUnit.h"
#include "Barn.h"
#include "SoilState.h"
#include "DrySoil.h"
#include "FruitfulSoil.h"
#include "FloodedSoil.h"

#include <cstdlib>

class CropField : public FarmUnit
{
private:
  SoilState *soilState;
  bool fertilizer;

public:
  CropField(std::string crop, int capacity);
  int getTotalCapacity() const override;
  std::string getCropType() const override;
  std::string getSoilStateName() const;
  void increaseProduction();
  void harvest();
  int getLeftoverCapacity() const override;
  void notify() {};
  void addCrops(int cropAmount) override;
  int removeCrops(int cropAmount) override;
  void setState(SoilState *soilState);
  void rain();
  ~CropField();
};
#endif