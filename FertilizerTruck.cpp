#include "FertilizerTruck.h"
#include <iostream>

FertilizerTruck::FertilizerTruck(std::vector<std::vector<FarmUnit*>>& map, int capacity)
    : Truck(map, capacity)
{
}

void FertilizerTruck::startEngine()
{
  this->findShortestPath();
  for(FarmUnit* unit : farmVector)
  {
    // if(FertilizerDecorator* fert = dynamic_cast<FertilizerDecorator*>(unit))
    // {
    //     fert->increaseProduction();
    // }
    // else if(CropField* crop = dynamic_cast<CropField*>(unit))
    // {
    //     crop->removeCrops(100);
    // }
  }
}

FertilizerTruck* FertilizerTruck::clone() const
{
  return new FertilizerTruck(*this);
}