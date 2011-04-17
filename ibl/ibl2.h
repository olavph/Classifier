#ifndef IBL2_H
#define IBL2_H

#include "ibl.h"

class IBL2 : public IBL
{
public:
    IBL2();
    virtual void train(const QVector<Datum*> trainSet, const DistanceCalculation * dc);
};

#endif // IBL2_H
