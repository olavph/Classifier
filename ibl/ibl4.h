#ifndef IBL4_H
#define IBL4_H

#include "ibl.h"
#include "classificationrecord.h"
#include <QHash>
#include <QVector>

class IBL4 : public IBL
{
private:
    QHash<const Datum*, ClassificationRecord> precisionIntervals;
    QHash<const Class*, ClassificationRecord> frequencyIntervals;
    QHash<const Class*, QVector<double> > attributeWeights;
public:
    static const double PRECISION_INTERVAL_Z = 0.9;
    static const double FREQUENCY_INTERVAL_Z = 0.75;
public:
    IBL4();
    virtual void train(const QSet<Datum*> trainSet, const DistanceCalculation * dc);
    virtual int similarity(const Datum * d1, const Datum * d2, const DistanceCalculation * dc) const;
    virtual bool acceptable(const Datum * d) const;
    virtual bool rejectable(const Datum * d) const;
};

#endif // IBL4_H
