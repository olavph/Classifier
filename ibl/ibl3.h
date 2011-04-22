#ifndef IBL3_H
#define IBL3_H

#include "ibl.h"
#include "classificationrecord.h"
#include <QHash>

class IBL3 : public IBL
{
private:
    QHash<const Datum*, ClassificationRecord> precisionIntervals;
    QHash<const Class*, ClassificationRecord> frequencyIntervals;
public:
    static const double PRECISION_INTERVAL_Z = 0.9;
    static const double FREQUENCY_INTERVAL_Z = 0.75;
public:
    IBL3();
    virtual void train(const QVector<Datum*> trainSet, const DistanceCalculation * dc);
    virtual bool acceptable(const Datum * d) const;
    virtual bool rejectable(const Datum * d) const;
};

#endif // IBL3_H
