#include "datum.h"
#include "class.h"
#include "distancecalculation.h"
#include <QSet>
#include <QPair>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

using namespace std;

class Classifier
{
public:
    Classifier();
    static void nN(DistanceCalculation * algorithm, Datum * toBeClassified, const QSet<Datum*> & classifiedData);
    static void kNN(DistanceCalculation * algorithm, const size_t k, Datum * toBeClassified, const QSet<Datum*> & classifiedData);
};

#endif // CLASSIFIER_H
