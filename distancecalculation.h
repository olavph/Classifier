#ifndef DISTANCECALCULATION_H
#define DISTANCECALCULATION_H

#include "datum.h"

class DistanceCalculation
{
public:
    DistanceCalculation() {};
    virtual double distance(Datum & d1, Datum & d2) = 0;
};

#endif // DISTANCECALCULATION_H
