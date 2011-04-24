#ifndef IBL1_H
#define IBL1_H

#include "ibl.h"

class IBL1 : public IBL
{
public:
    IBL1();
    virtual void train(const QSet<Datum*> trainSet, const DistanceCalculation * dc);
};

#endif // IBL1_H
