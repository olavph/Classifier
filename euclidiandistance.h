#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H

#include "distancecalculation.h"
#include <math.h>

class EuclidianDistance : public DistanceCalculation
{
public:
    EuclidianDistance() {};
    double distance(const Datum * d1, const Datum * d2)
    {
        double euclidianDistance = 0;
        if (d1->getDimensions() != d2->getDimensions()){
            return -1;
        }
        for(unsigned int i = 0; i < d1->getDimensions(); i++){
            euclidianDistance += fabs(pow((d1->getCoordinate(i) - d2->getCoordinate(i)),2.0));
        }
        return sqrt(euclidianDistance);
    }
};

#endif // EUCLIDIANDISTANCE_H
