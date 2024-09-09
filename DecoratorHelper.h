#ifndef DECORATORHELPER_H
#define DECORATORHELPER_H
#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include "FertilizerDecorator.h"
#include <typeinfo>

class DecoratorHelper
{
public:
    static bool hasDecorator(FarmUnit *unit, const std::type_info &decoratorType)
    {
        while (unit)
        {
            if (typeid(*unit) == decoratorType)
            {
                return true;
            }
            if (auto bd = dynamic_cast<ExtraBarnDecorator *>(unit))
            {
                unit = bd->getWrappedUnit();
            }
            else if (auto fd = dynamic_cast<FertilizerDecorator *>(unit))
            {
                unit = fd->getWrappedUnit();
            }
            else
            {
                break;
            }
        }
        return false;
    }
};
#endif