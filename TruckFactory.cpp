#include "TruckFactory.h"

TruckFactory::TruckFactory(std::vector<std::vector<FarmUnit*>>& map) : map(map)
{

}

Truck* TruckFactory::buy(std::string type)
{
  if(type == "Delivery")
  {
    return new DeliveryTruck(map,100);
  }
  else if(type == "Fertilizer")
  {
    return new FertilizerTruck(map,5);
  }
  else
  {
    return nullptr;
  }
}

void TruckFactory::sell(Truck* truck)
{
  if(truck != nullptr && truck != NULL)
  {
    delete truck;
    truck = nullptr;
  }
}

void TruckFactory::callTruck(Truck* truck)
{
  truck->startEngine();
}