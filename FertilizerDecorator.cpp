#include "FertilizerDecorator.h"

void FertilizerDecorator::checkFertilizer()
{
    if (fertilizerAmount == 0)
    {
        // TODO: Call fertilizer truck
    }
}
FertilizerDecorator::FertilizerDecorator(FarmUnit *unit) : FarmUnitDecorator(unit)
{
    this->unit = unit;
}

FertilizerDecorator::~FertilizerDecorator()
{
    delete this->unit;
}

int FertilizerDecorator::getTotalCapacity() const
{
    return this->unit->getTotalCapacity();
}

std::string FertilizerDecorator::getCropType() const
{
    return this->unit->getCropType();
}

std::string FertilizerDecorator::getSoilStateName() const
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        return cropField->getSoilStateName();
    }
    return "Not a cropfield";
}

void FertilizerDecorator::increaseProduction()
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        cropField->increaseProduction();
    }
}

void FertilizerDecorator::notifyDelivery()
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        cropField->notifyDelivery();
    }
}

void FertilizerDecorator::notifyFertilizer()
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        cropField->notifyFertilizer();
    }
}

void FertilizerDecorator::harvest()
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        cropField->harvest();
    }
}

int FertilizerDecorator::getLeftoverCapacity() const
{
    return this->unit->getLeftoverCapacity();
}

void FertilizerDecorator::addCrops(int amount)
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        if (cropField->getLeftoverCapacity() > 0)
        {
            cropField->addCrops(amount - cropField->getLeftoverCapacity());
        }
        this->unit->addCrops(amount);
    }
}

int FertilizerDecorator::removeCrops(int amount)
{
    int total = 0;
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        total += cropField->removeCrops(amount);
        if (total != amount)
        {
            this->unit->removeCrops(amount - total);
        }
    }
    return total;
}

void FertilizerDecorator::rain()
{
    CropField *cropField = dynamic_cast<CropField *>(this->unit);
    if (cropField)
    {
        int rando = rand() % 3;
        // No rain
        if (rando == 0)
        {
            fertilizerAmount--;
            cropField->setState(new FruitfulSoil());
            return;
        }
        // Rain
        else if (rando == 1)
        {
            int random = rand() % 3;
            // Flood
            if (random == 0)
            {
                cropField->setState(new FloodedSoil());
                return;
            }
            // Rain
            cropField->setState(new FruitfulSoil());
        }
    }
}