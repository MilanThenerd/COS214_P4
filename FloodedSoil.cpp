#include "FloodedSoil.h"

int FloodedSoil::harvestCrops() const
{
  return 0;
}

SoilState* FloodedSoil::rain()
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

std::string FloodedSoil::getName() const
{
  return "Flooded";
}
