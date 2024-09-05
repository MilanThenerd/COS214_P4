#include "CropField.h"

#include <iostream>

CropField::CropField(std::string crop , int capacity)
{
  this->cropType = crop;
  this->totalCapacity = capacity;
  this->currentStored = 0;
  this->soilState = new DrySoil();
  extraBarn = nullptr; 
}

int CropField::getTotalCapacity() const
{
  return extraBarn ? totalCapacity + extraBarn->getTotalCapacity() : totalCapacity;
}

int CropField::getLeftoverCapacity() const 
{
  return (totalCapacity - currentStored) + (extraBarn ? extraBarn->getLeftoverCapacity() : 0);
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

void CropField::addExtraBarn()
{
  extraBarn = new Barn(this->cropType, totalCapacity/2);
}

void CropField::removeExtraBarn()
{
  if(hasExtraBarn())
  {
    delete extraBarn;
    extraBarn = nullptr;
  }
}

void CropField::addCrops(int amount)
{
  currentStored += amount;
  if(currentStored > getTotalCapacity())
  {
    if(extraBarn)
    {
      extraBarn->addCrops(currentStored-totalCapacity);
      currentStored -= totalCapacity;
    }
    else
    {
      currentStored = totalCapacity;
    }
  }
}

int CropField::removeCrops(int amount)
{
  int total = 0;
  if (extraBarn) 
  {
    int amountInBarn = extraBarn->getTotalCapacity() - extraBarn->getLeftoverCapacity();
    if (amountInBarn >= amount) 
    {
      return extraBarn->removeCrops(amount);
    } 
    else 
    {
      total += extraBarn->removeCrops(amountInBarn);
      amount -= amountInBarn;
    }
  }
  if (amount > currentStored) 
  {
    total += currentStored;
    currentStored = 0;
  } 
  else 
  {
    currentStored -= amount;
    total += amount;
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

bool CropField::hasExtraBarn()
{
  if(extraBarn)
  {
    return true;
  }
  return false;
}

CropField::~CropField()
{
  delete soilState;
  soilState = nullptr;
  if(extraBarn)
  {
    delete extraBarn;
    extraBarn = nullptr;
  }
}