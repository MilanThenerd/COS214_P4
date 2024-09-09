#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Truck.h"
#include "DeliveryTruck.h"
#include "FertilizerTruck.h"
#include "FarmUnit.h"

#include <queue>

class Publisher
{
private:
  std::vector<Truck *> truckVector;
  std::queue<std::pair<FarmUnit *, std::string>> queueFarm;

public:
  Publisher();
  void add(FarmUnit *unit, std::string orderType);
  void add(Truck *unit);
  bool handle();
  bool hasQueue() const;
  bool hasTruck() const;
  void removeTruck(Truck *truck);
  std::vector<Truck *> &getTrucks();
};
#endif