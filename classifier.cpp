#include "classifier.h"
#include <math.h>
#include <algorithm>
#include <QMap>

Classifier::Classifier()
{
}

void Classifier::nN(DistanceCalculation * algorithm, Datum * toBeClassified, const QSet<Datum*> & classifiedData)
{
    Datum * nearestNeighbour = *classifiedData.begin();
    double nearestDistance = algorithm->distance(nearestNeighbour, toBeClassified);
    foreach (Datum * classifiedDatum, classifiedData) {
        if(nearestDistance > algorithm->distance(classifiedDatum, toBeClassified)) {
            nearestNeighbour = classifiedDatum;
            nearestDistance = algorithm->distance(nearestNeighbour, toBeClassified);
        }
    }
    toBeClassified->myOwnSuperSecretClass = nearestNeighbour->myOwnSuperSecretClass;
}

bool cmp( QPair<double, Datum*> a, QPair<double, Datum*> b ) {
    return a.first > b.first;
}

void Classifier::kNN(DistanceCalculation * algorithm, const size_t k, Datum * toBeClassified, const QSet<Datum*> & classifiedData)
{
    QVector< QPair<double, Datum*> > distances;
    foreach (Datum * compared, classifiedData) {
        distances.push_back(QPair<double, Datum*>(algorithm->distance(toBeClassified, compared), compared));
    }
    sort(distances.begin(), distances.end(), cmp);

    QMap<Class*, int> classCounts;
    for(size_t i = 1; i <= k; i++) {
        Class * c = distances.at(distances.size()-i).second->myOwnSuperSecretClass;
        classCounts[c] ++;
    }
    QMap<Class*, int>::iterator mapIt;
    QMap<Class*, int>::iterator result = classCounts.begin();
    for(mapIt = classCounts.begin(); mapIt != classCounts.end(); mapIt++) {
        if(mapIt.value() > result.value())
            result = mapIt;
    }
    toBeClassified->myOwnSuperSecretClass = result.key();
}
