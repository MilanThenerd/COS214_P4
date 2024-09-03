#ifndef FLOODEDSOIL_H
#define FLOODEDSOIL_H

#include "SoilState.h"
#include "DrySoil.h"
#include "FruitfulSoil.h"

class FloodedSoil : public SoilState 
{
public:
    int harvestCrops() const override;
    SoilState* rain() override;
    std::string getName() const override;
};
#endif