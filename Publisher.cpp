#include "Publisher.h"

#include <algorithm> 

Publisher::Publisher()
{

}

void Publisher::add(FarmUnit* farm, std::string orderType)
{
  this->queueFarm.push(std::make_pair(farm,orderType));
}

void Publisher::add(Truck* unit)
{
  this->truckVector.push_back(unit);
}

std::vector<Truck*>& Publisher::getTrucks()
{
  return this->truckVector;
}

void Publisher::removeTruck(Truck* truck)
{
  auto& trucks = getTrucks();
  auto it = std::find(trucks.begin(), trucks.end(), truck);
  if (it != trucks.end())
  {
    trucks.erase(it); 
  }
}

bool Publisher::handle()
{
  std::size_t truckIndex = 0;

  while (!queueFarm.empty())
  {
    if (truckVector.empty())
    {
      return false;
    }
    FarmUnit* farm = this->queueFarm.front().first;
    std::string orderType = this->queueFarm.front().second;
    Truck* truck = this->truckVector[truckIndex];
    if (truck == nullptr)
    {
      truckIndex = (truckIndex + 1) % truckVector.size();
      continue;
    }

    bool handled = false;

    if (orderType == "Delivery")
    {
      if (DeliveryTruck* deliveryTruck = dynamic_cast<DeliveryTruck*>(truck))
      {
        handled = deliveryTruck->callTruck(farm);
      }
    }
    else if (orderType == "Fertilizer")
    {
      if (FertilizerTruck* fertilizerTruck = dynamic_cast<FertilizerTruck*>(truck))
      {
        handled = fertilizerTruck->callTruck(farm);
      }
    }
    if (handled)
    {
      queueFarm.pop();
    }
    else
    {
      truckIndex = (truckIndex + 1) % truckVector.size();
    }
    if (truckIndex == 0 && !handled)
    {
      return false;
    }
  }
  return true;
}

bool Publisher::hasQueue() const
{
  if(this->queueFarm.size() > 0)
  {
    return true;
  }
  return false;
}

bool Publisher::hasTruck() const
{

  if(this->truckVector.size() > 0)
  {
    return true;
  }
  return false;
}
