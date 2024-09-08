#ifndef DELIVERYTRUCK_H
#define DELIVERYTRUCK_H

#include "Truck.h"
#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include "CropField.h"

class DeliveryTruck : public Truck
{
  public:
    DeliveryTruck(std::vector<std::vector<FarmUnit*>>& map , int capacity);
    void startEngine() override;
    DeliveryTruck* clone() const override;
};
#endif