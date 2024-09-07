#include "RegularSoil.h"

int RegularSoil::harvestCrops() const
{
  return 2;
}

SoilState *RegularSoil::rain()
{
  int random = rand() % 2;
  // No rain
  if (random == 0)
  {
    return new DrySoil();
  }
  // Rain
  else if (random == 1)
  {
    return new FruitfulSoil();
  }
}

std::string RegularSoil::getName() const
{
  return "Regular";
}
