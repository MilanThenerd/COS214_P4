#include "FloodedSoil.h"
#include <iostream>

FloodedSoil::FloodedSoil(int roundsleft) : roundsLeft(roundsleft)
{
}

int FloodedSoil::harvestCrops() const
{
  return 0;
}

SoilState *FloodedSoil::rain()
{
  roundsLeft--;
  if (roundsLeft > 0)
  {
    std::cout << "Flooded soil: " << roundsLeft << " rounds left" << std::endl;
    return new FloodedSoil(roundsLeft);
  }
  std::cout << "Flooded soil: turning into fruitful soil" << std::endl;
  return new FruitfulSoil();
}

std::string FloodedSoil::getName() const
{
  return "Flooded";
}
