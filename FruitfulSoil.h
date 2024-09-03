#ifndef FRUITFULSOIL_H
#define FRUITFULSOIL_H

#include "SoilState.h"
#include "DrySoil.h"
#include "FloodedSoil.h"

class FruitfulSoil : public SoilState
{
  public:
    int harvestCrops() const override;
    SoilState* rain() override;
    std::string getName() const override;
};
#endif