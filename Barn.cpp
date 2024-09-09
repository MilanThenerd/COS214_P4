#include "Barn.h"

Barn::Barn(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY)
{
  this->cropType = "None";
  this->totalCapacity = 0;
  this->currentStored = 0;
  this->iterator = new FarmTraversalBFS(farmMap, startX, startY);
}

int Barn::getTotalCapacity() const
{
  return totalCapacity;
}

int Barn::getLeftoverCapacity() const
{
  return totalCapacity - currentStored;
}

std::string Barn::getCropType() const
{
  return cropType;
}

void Barn::addCrops(int amount)
{
  if (getLeftoverCapacity() == 0)
  {
    return;
  }
  currentStored += amount;
  if (currentStored > totalCapacity)
  {
    currentStored = totalCapacity;
  }
}

int Barn::removeCrops(int amount)
{
  if (currentStored < amount)
  {
    int amountBack = currentStored;
    currentStored = 0;
    return amountBack;
  }
  currentStored -= amount;
  return amount;
}