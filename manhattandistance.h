#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "distancecalculation.h"
#include <math.h>

class ManhattanDistance : public DistanceCalculation
{
public:
    ManhattanDistance() {};
    double distance(const Datum * d1, const Datum * d2)
    {
        double manhattanDistance = 0;
        if (d1->getDimensions() != d2->getDimensions()){
            return -1;
        }
        for(unsigned int i = 0; i < d1->getDimensions(); i++){
            manhattanDistance += fabs(d1->getCoordinate(i) - d2->getCoordinate(i));
        }
        return manhattanDistance;
    }
};

#endif // MANHATTANDISTANCE_H
