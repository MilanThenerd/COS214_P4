#include "ExtraBarnDecorator.h"

ExtraBarnDecorator::ExtraBarnDecorator(FarmUnit *unit) : FarmUnitDecorator(unit)
{
  this->unit = unit;
}

ExtraBarnDecorator::~ExtraBarnDecorator()
{
  delete this->unit;
}

int ExtraBarnDecorator::getTotalCapacity() const
{
  return this->unit->getTotalCapacity();
}

std::string ExtraBarnDecorator::getCropType() const
{
  return this->unit->getCropType();
}

std::string ExtraBarnDecorator::getSoilStateName() const
{
  CropField *cropField = dynamic_cast<CropField *>(this->unit);
  if (cropField)
  {
    return cropField->getSoilStateName();
  }
  return "Not a cropfield";
}

void ExtraBarnDecorator::harvest()
{
  CropField *cropField = dynamic_cast<CropField *>(this->unit);
  if (cropField)
  {
    cropField->harvest();
  }
}

int ExtraBarnDecorator::getLeftoverCapacity() const
{
  return this->unit->getLeftoverCapacity();
}

void ExtraBarnDecorator::notifyDelivery()
{
  CropField *cropField = dynamic_cast<CropField *>(this->unit);
  if (cropField)
  {
    cropField->notifyDelivery();
  }
}

void ExtraBarnDecorator::addCrops(int amount)
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

int ExtraBarnDecorator::removeCrops(int amount)
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

void ExtraBarnDecorator::rain()
{
  CropField *cropField = dynamic_cast<CropField *>(this->unit);
  if (cropField)
  {
    cropField->rain();
  }
}