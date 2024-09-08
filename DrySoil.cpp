#include "DrySoil.h"

int DrySoil::harvestCrops() const
{
  return 1;
}

SoilState* DrySoil::rain()
{
  int random = rand() % 3;
  if (random == 0) 
  {
    return new DrySoil();
  } 
  else if (random == 1) 
  {
      return new FruitfulSoil();
  } 
  else 
  {
    return new FloodedSoil();
  }
}

std::string DrySoil::getName() const
{
  return "Dry";
}
