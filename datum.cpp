#include "Datum.h"

Datum::Datum(double x)
{
    coordinates = new QVector<double>();
    coordinates->push_back(x);
}

Datum::Datum(double x, double y)
{
    coordinates = new QVector<double>();
    coordinates->push_back(x);
    coordinates->push_back(y);
}

Datum::Datum(double x, double y, double z)
{
    coordinates = new QVector<double>();
    coordinates->push_back(x);
    coordinates->push_back(y);
    coordinates->push_back(z);
}

Datum::Datum(QVector<double> coord)
{
    coordinates = new QVector<double>(coord);

}

double Datum::getCoordinate(int index) const
{
    return coordinates->at(index);
}

unsigned int Datum::getDimensions() const
{
    return coordinates->count();
}

