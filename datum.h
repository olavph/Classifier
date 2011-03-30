#include <QVector>

#ifndef DATUM_H
#define DATUM_H

class Datum
{
public:
    Datum() {};
    Datum(double x);
    Datum(double x, double y);
    Datum(double x, double y, double z);
    Datum(QVector<double> coordinates);
    void addCoordinate(double coord);
    double getCoordinate(int index) const;
    unsigned int getDimensions() const;

private:
    QVector<double> * coordinates;
};

#endif // DATUM_H
