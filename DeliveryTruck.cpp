#include "DeliveryTruck.h"
#include <iostream>

DeliveryTruck::DeliveryTruck(std::vector<std::vector<FarmUnit*>>& map, int capacity)
    : Truck(map, capacity)
{
}

void DeliveryTruck::startEngine()
{
  this->findShortestPath();
  for(FarmUnit* unit : farmVector)
  {
    if(ExtraBarnDecorator* barn = dynamic_cast<ExtraBarnDecorator*>(unit))
    {
      barn->removeCrops(200);
    }
    else if(CropField* crop = dynamic_cast<CropField*>(unit))
    {
      crop->removeCrops(100);
    }
  }
}

DeliveryTruck* DeliveryTruck::clone() const
{
  return new DeliveryTruck(*this);
}

