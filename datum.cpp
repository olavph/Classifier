#include "Datum.h"

Datum::Datum(double x, Class * myClass)
{
    coordinates.push_back(x);
    myOwnSuperSecretClass = myClass;
}

Datum::Datum(double x, double y, Class * myClass)
{
    coordinates.push_back(x);
    coordinates.push_back(y);
    myOwnSuperSecretClass = myClass;
}

Datum::Datum(double x, double y, double z, Class * myClass)
{
    coordinates.push_back(x);
    coordinates.push_back(y);
    coordinates.push_back(z);
    myOwnSuperSecretClass = myClass;
}

Datum::Datum(QVector<double> coord, Class * myClass)
{
    myOwnSuperSecretClass = myClass;

}

double Datum::getCoordinate(int index) const
{
    return coordinates.at(index);
}

unsigned int Datum::getDimensions() const
{
    return coordinates.count();
}

