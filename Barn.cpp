#include "Barn.h"

Barn::Barn(std::string crop , int capacity)
{
  this->cropType = crop;
  this->totalCapacity = capacity;
  this->currentStored = 0;
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
  if(getLeftoverCapacity() == 0)
  {
    return;
  }
  currentStored += amount;
  if(currentStored > totalCapacity)
  {
    currentStored = totalCapacity;
  }
}

int Barn::removeCrops(int amount)
{
  if(currentStored < amount)
  {
    int amountBack = currentStored;
    currentStored = 0;
    return amountBack;
  }
  currentStored -= amount;
  return amount;
}