#include "FruitfulSoil.h"

int FruitfulSoil::harvestCrops() const
{
  return 3;
}

SoilState *FruitfulSoil::rain()
{
  int random = rand() % 2;
  // No rain
  if (random == 0)
  {
    return new RegularSoil();
  }
  // Rain
  else if (random == 1)
  {
    int random2 = rand() % 5;
    if (random2 == 0)
    {
      return new FloodedSoil();
    }
  }
  return new FruitfulSoil();
}

std::string FruitfulSoil::getName() const
{
  return "Fruitful";
}
