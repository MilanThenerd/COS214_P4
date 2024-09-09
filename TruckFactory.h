#ifndef TRUCKFACTORY_H
#define TRUCKFACTORY_H

#include "Truck.h"
#include "DeliveryTruck.h"
#include "FertilizerTruck.h"

class TruckFactory
{
  private:
    std::vector<std::vector<FarmUnit*>> map;
  public:
    TruckFactory(std::vector<std::vector<FarmUnit*>>& map);
    Truck* buy(std::string);
    void sell(Truck*);
    void callTruck(Truck*);
};
#endif