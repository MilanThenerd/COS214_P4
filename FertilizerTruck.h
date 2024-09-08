#ifndef FERTILIZERTRUCK_H
#define FERTILIZERTRUCK_H

#include "Truck.h"
#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include "CropField.h"

class FertilizerTruck : public Truck
{
  public:
    FertilizerTruck(std::vector<std::vector<FarmUnit*>>& map , int capacity);
    void startEngine() override;
    FertilizerTruck* clone() const override;
};
#endif