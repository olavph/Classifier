#ifndef IBL_H
#define IBL_H

#include <QSet>
#include "datum.h"
#include "distancecalculation.h"

class IBL
{
protected:
    QSet<Datum*> _conceptualDescriptor;
    QSet<Datum*> _incorrectlyClassifiedData;
public:
    IBL();
    virtual void train(const QSet<Datum*> trainSet, const DistanceCalculation * dc) = 0;
    virtual int similarity(const Datum * d1, const Datum * d2, const DistanceCalculation * dc) const;
    virtual bool acceptable(const Datum * d) const;
    virtual bool rejectable(const Datum * d) const;
    QSet<Datum*> & conceptualDescriptor() {return _conceptualDescriptor;}
    QSet<Datum*> & incorrectlyClassifiedData() {return _incorrectlyClassifiedData;}
    int numberOfIncorrectlyClassified() const {return _incorrectlyClassifiedData.size();}
};

#endif // IBL_H
