#include <QVector>
#include "class.h"

#ifndef DATUM_H
#define DATUM_H

class Datum
{
public:
    Datum() {};
    Datum(double x, Class * myClass = NULL);
    Datum(double x, double y, Class * myClass = NULL);
    Datum(double x, double y, double z, Class * myClass = NULL);
    Datum(QVector<double> coordinates, Class * myClass = NULL);
    void addCoordinate(double coord);
    double getCoordinate(int index) const;
    unsigned int getDimensions() const;


    Class * myOwnSuperSecretClass; //TODO refactor!

private:
    QVector<double> * coordinates;
};

#endif // DATUM_H
