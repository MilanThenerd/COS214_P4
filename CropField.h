#ifndef CROPFIELD_H
#define CROPFIELD_H

#include "FarmUnit.h"
#include "SoilState.h"
#include "DrySoil.h"
#include "FarmTraversalBFS.h"
#include "Publisher.h"
#include <cstdlib>

class Publisher;

class CropField : public FarmUnit
{
private:
  SoilState *soilState;
  bool fertilizer;
  FarmTraversal *farmIterator;
  Publisher* publisher;

public:
  CropField(std::string crop, int capacity , Publisher* publisher);
  int getTotalCapacity() const override;
  std::string getCropType() const override;
  std::string getSoilStateName() const;
  void increaseProduction();
  void harvest();
  int getLeftoverCapacity() const override;
  void notifyDelivery();
  void notifyFertilizer();
  void addCrops(int cropAmount) override;
  int removeCrops(int cropAmount) override;
  void setState(SoilState *soilState);
  void rain();
  ~CropField();
};
#endif