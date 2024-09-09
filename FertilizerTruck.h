#ifndef FERTILIZERTRUCK_H
#define FERTILIZERTRUCK_H

#include "Truck.h"
#include "FarmUnit.h"
#include "CropField.h"
#include "FertilizerDecorator.h"

class FertilizerTruck : public Truck
{
  public:
    FertilizerTruck(std::vector<std::vector<FarmUnit*>>& map , int capacity);
    void startEngine() override;
    FertilizerTruck* clone() const override;
};
#endif