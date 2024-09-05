#include "CropField.h"

#include <iostream>

CropField::CropField(std::string crop , int capacity)
{
  this->cropType = crop;
  this->totalCapacity = capacity;
  this->currentStored = 0;
  this->soilState = new DrySoil();
}

int CropField::getTotalCapacity() const
{
  return totalCapacity;
}

int CropField::getLeftoverCapacity() const 
{
  return (totalCapacity - currentStored);
}

std::string CropField::getCropType() const
{
  return cropType;
}

std::string CropField::getSoilStateName() const
{
  return this->soilState->getName();
}

void CropField::increaseProduction()
{
  fertilizer = true;
}

void CropField::harvest()
{
  int crops = soilState->harvestCrops();
  if(fertilizer)
  {
    crops *= 2;
    fertilizer = false;
  }
  addCrops(crops);
}

void CropField::addCrops(int amount)
{
  currentStored += amount;
  if(currentStored > getTotalCapacity())
  {
    currentStored = totalCapacity;
  }
}

int CropField::removeCrops(int amount)
{
  int total = 0;
  if (amount > currentStored) 
  {
    total = currentStored;
    currentStored = 0;
  } 
  else 
  {
    currentStored -= amount;
    total = amount;
  }
  return total;
}

void CropField::rain()
{
  static bool seeded = false;
  if (!seeded) 
  {
    srand(static_cast<unsigned int>(time(0)));
    seeded = true;
  }
  SoilState* newState = soilState->rain();
  if(newState != soilState)
  {
    delete soilState;
    soilState = newState;
  }
}

CropField::~CropField()
{
  delete soilState;
  soilState = nullptr;
}