#include "FloodedSoil.h"

int FloodedSoil::harvestCrops() const
{
  return 0;
}

SoilState *FloodedSoil::rain()
{
  roundsLeft--;
  if (roundsLeft > 0)
  {
    return new FloodedSoil();
  }

  int random = rand() % 2;
  // No rain
  if (random == 0)
  {
    return new FruitfulSoil();
  }
  // Rain
  else if (random == 1)
  {
    return new FloodedSoil();
  }
}

std::string FloodedSoil::getName() const
{
  return "Flooded";
}
