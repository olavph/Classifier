#ifndef IBL_H
#define IBL_H

#include <QVector>
#include "datum.h"
#include "distancecalculation.h"

class IBL
{
protected:
    QVector<Datum*> _conceptualDescriptor;
    QVector<Datum*> _incorrectlyClassifiedData;
public:
    IBL() {};
    virtual void train(const QVector<Datum*> trainSet, const DistanceCalculation * dc) = 0;
    QVector<Datum*> & conceptualDescriptor() {return _conceptualDescriptor;}
    QVector<Datum*> & incorrectlyClassifiedData() {return _incorrectlyClassifiedData;}
    int numberOfIncorrectlyClassified() const {return _incorrectlyClassifiedData.size();}
};

#endif // IBL_H
