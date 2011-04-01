#include "datum.h"
#include "class.h"
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
    static void nNEuclidian(Datum & d, const QVector<Datum> & classifiedData);
    static void kNNEuclidian(const size_t k, Datum & d, const QVector<Datum> & classifiedData);
    static void nNManhattan(Datum & toBeClassified, const QVector<Datum> & data);
    static void kNNManhattan(const size_t k, Datum & d, const QVector<Datum> & classifiedData);

};

#endif // CLASSIFIER_H
