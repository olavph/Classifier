#include "datum.h"
#include "class.h"
#include "distancecalculation.h"
#include "QVector"
#include "QPair"

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

using namespace std;

class Classifier
{
public:
    Classifier();
    static double manhattan(Datum & d1, Datum & d2);
    static double euclidian(Datum & d1, Datum & d2);
    static void nN(DistanceCalculation * algorithm, Datum & toBeClassified, const QVector<Datum> & classifiedData);
    static void kNN(DistanceCalculation * algorithm, const size_t k, Datum & toBeClassified, const QVector<Datum> & classifiedData);
};

#endif // CLASSIFIER_H
