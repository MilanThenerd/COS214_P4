#ifndef REGULARSOIL_H
#define REGULARSOIL_H

#include "SoilState.h"
#include "DrySoil.h"
#include "FruitfulSoil.h"

class RegularSoil : public SoilState
{
public:
    int harvestCrops() const override;
    SoilState *rain() override;
    std::string getName() const override;
};
#endif