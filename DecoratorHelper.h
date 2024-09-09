#ifndef DECORATORHELPER_H
#define DECORATORHELPER_H

#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include "FertilizerDecorator.h"
#include <typeinfo>

/**
 * @class DecoratorHelper
 * @brief Utility class for working with decorators on FarmUnit objects.
 *
 * The DecoratorHelper class provides static utility functions for checking
 * if a FarmUnit object has a specific type of decorator.
 */
class DecoratorHelper
{
public:
    /**
     * @brief Checks if a FarmUnit has a specific type of decorator.
     *
     * This function traverses the decorators applied to a FarmUnit and checks
     * if any of them match the specified decorator type.
     *
     * @param unit Pointer to the FarmUnit to check.
     * @param decoratorType The type_info of the decorator to check for.
     * @return True if the FarmUnit has the specified decorator, false otherwise.
     */
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

#endif // DECORATORHELPER_H