#include "DrySoil.h"

int DrySoil::harvestCrops() const
{
  return 1;
}

SoilState *DrySoil::rain()
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
    return new RegularSoil();
  }
}

std::string DrySoil::getName() const
{
  return "Dry";
}
