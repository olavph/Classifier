#ifndef DISTANCECALCULATION_H
#define DISTANCECALCULATION_H

#include "datum.h"

class DistanceCalculation
{
public:
    DistanceCalculation() {};
    virtual double distance(const Datum * d1, const Datum * d2) = 0;
};

#endif // DISTANCECALCULATION_H
