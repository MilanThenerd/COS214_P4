#ifndef DRYSOIL_H
#define DRYSOIL_H

#include "SoilState.h"
#include "FruitfulSoil.h"
#include "FloodedSoil.h"

class DrySoil : public SoilState
 {
public:
    int harvestCrops() const override;
    SoilState* rain() override;
    std::string getName() const override;
};
#endif