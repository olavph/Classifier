#include "ibl.h"

IBL::IBL()
{
}

int IBL::similarity(const Datum * d1, const Datum * d2, const DistanceCalculation * dc) const
{
    return -dc->distance(d1, d2);
}

bool IBL::acceptable(const Datum  * d) const
{
    return false;
}

bool IBL::rejectable(const Datum * d) const
{
    return false;
}
