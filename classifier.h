#include "datum.h"
#include "class.h"
#include <vector>

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

using namespace std;

class Classifier
{
public:
    Classifier();
    double manhattan(Datum d1, Datum d2);
    double euclidian(Datum d1, Datum d2);
    Class nN(Datum d);
    Class kNN(Datum d);

private:
    vector< pair<Datum, Class> > classifiedDatum();

};

#endif // CLASSIFIER_H
