#include "Barn.h"

void Barn::setup()
{
  iterator->initialize();
  iterator->firstFarm();

  while (iterator->hasNext())
  {
    int idx = iterator->getCurrentIndex();
    Coords c = iterator->getPath()[idx];

    if (c[coords] <= 1 && c[coords] > 0)
    {
      if (!DecoratorHelper::hasDecorator(farmMap[c.x][c.y], typeid(ExtraBarnDecorator)))
        farmMap[c.x][c.y] = new ExtraBarnDecorator(farmMap[c.x][c.y]);
    }

    iterator->next();
  }
}

Barn::Barn(std::vector<std::vector<FarmUnit *>> &fm, int startX, int startY) : coords(Coords(startX, startY)), farmMap(fm)
{
  this->cropType = "None";
  this->totalCapacity = 0;
  this->currentStored = 0;
  this->iterator = new FarmTraversalBFS(fm, startX, startY);
  setup();
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