#include <QVector>

#ifndef DADO_H
#define DADO_H

class dado
{
public:
    dado(double x);
    dado(double x, double y);
    dado(double x, double y, double z);
    dado(int dimensions, QVector<double> coordenadas);
    void addCoord(double coord);
    double getCoord(int pos);
    int getDimensions();

private:
    int dimensions;
    QVector<double> *vec;
};

#endif // DADO_H
