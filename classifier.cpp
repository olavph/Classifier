#include "classifier.h"
#include <math.h>
#include <algorithm>
#include <QMap>

Classifier::Classifier()
{
}

double Classifier::manhattan(Datum & d1, Datum & d2)
{
    double manhattanDistance = 0;
    if (d1.getDimensions() != d2.getDimensions()){
        return -1;
    }
    for(unsigned int i = 0; i < d1.getDimensions(); i++){
        manhattanDistance += fabs(d1.getCoordinate(i) - d2.getCoordinate(i));
    }
    return manhattanDistance;
}

double Classifier::euclidian(Datum & d1, Datum & d2)
{
    double euclidianDistance = 0;
    if (d1.getDimensions() != d2.getDimensions()){
        return -1;
    }
    for(unsigned int i = 0; i < d1.getDimensions(); i++){
        euclidianDistance += fabs(pow((d1.getCoordinate(i) - d2.getCoordinate(i)),2.0));
    }
    return sqrt(euclidianDistance);
}

void Classifier::nNEuclidian(Datum & toBeClassified, const QVector<Datum> & data)
{
    Datum nearestNeighbour = data.at(0);
    Datum classifiedDatum;
    for(int i = 1; i < data.size(); i++){
        classifiedDatum = data.at(i);
        if(euclidian(nearestNeighbour, toBeClassified) > euclidian(classifiedDatum, toBeClassified))
        {
            nearestNeighbour = classifiedDatum;
        }
    }
    toBeClassified.myOwnSuperSecretClass = nearestNeighbour.myOwnSuperSecretClass;
}

bool cmp( QPair<double, Datum> a, QPair<double, Datum> b ) {
  return a.first > b.first;
}

void Classifier::kNNEuclidian(const size_t k, Datum & toBeClassified, const QVector<Datum> & data)
{
    QVector< QPair<double, Datum> > distances;
    for(int i = 0; i < data.size(); i++) {
        Datum compared = data.at(i);
        distances.push_back(QPair<double, Datum>(euclidian(toBeClassified, compared), compared));
    }
    sort(distances.begin(), distances.end(), cmp);

    QMap<Class*, int> classCounts;
    for(size_t i = 1; i <= k; i++) {
        Class * c = distances.at(distances.size()-i).second.myOwnSuperSecretClass;
        classCounts[c] ++;
    }
    QMap<Class*, int>::iterator mapIt;
    QMap<Class*, int>::iterator result = classCounts.begin();
    for(mapIt = classCounts.begin(); mapIt != classCounts.end(); mapIt++) {
        if(mapIt.value() > result.value())
            result = mapIt;
    }
    toBeClassified.myOwnSuperSecretClass = result.key();
}


void Classifier::nNManhattan(Datum & toBeClassified, const QVector<Datum> & data)
{
    Datum nearestNeighbour = data.at(0);
    Datum classifiedDatum;
    for(int i = 1; i < data.size(); i++){
        classifiedDatum = data.at(i);
        if(manhattan(nearestNeighbour, toBeClassified) > manhattan(classifiedDatum, toBeClassified))
        {
            nearestNeighbour = classifiedDatum;
        }
    }
    toBeClassified.myOwnSuperSecretClass = nearestNeighbour.myOwnSuperSecretClass;
}

void Classifier::kNNManhattan(const size_t k, Datum & toBeClassified, const QVector<Datum> & data)
{
    QVector< QPair<double, Datum> > distances;
    for(int i = 0; i < data.size(); i++) {
        Datum compared = data.at(i);
        distances.push_back(QPair<double, Datum>(manhattan(toBeClassified, compared), compared));
    }
    sort(distances.begin(), distances.end(), cmp);

    QMap<Class*, int> classCounts;
    for(size_t i = 1; i <= k; i++) {
        Class * c = distances.at(distances.size()-i).second.myOwnSuperSecretClass;
        classCounts[c] ++;
    }
    QMap<Class*, int>::iterator mapIt;
    QMap<Class*, int>::iterator result = classCounts.begin();
    for(mapIt = classCounts.begin(); mapIt != classCounts.end(); mapIt++) {
        if(mapIt.value() > result.value())
            result = mapIt;
    }
    toBeClassified.myOwnSuperSecretClass = result.key();
}

