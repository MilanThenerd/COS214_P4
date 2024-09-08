#include "FruitfulSoil.h"

int FruitfulSoil::harvestCrops() const
{
  return 3;
}

SoilState* FruitfulSoil::rain()
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

std::string FruitfulSoil::getName() const
{
  return "Fruitful";
}
