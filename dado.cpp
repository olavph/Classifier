#include "dado.h"

dado::dado(double x)
{
    this->dimensions=1;
    vec = new QVector<double>();
    this->vec->push_back(x);
}

dado::dado(double x, double y)
{
    this->dimensions=2;
    vec = new QVector<double>();
    this->vec->push_back(x);
    this->vec->push_back(y);
}

dado::dado(double x, double y, double z)
{
    this->dimensions=3;
    vec = new QVector<double>();
    this->vec->push_back(x);
    this->vec->push_back(y);
    this->vec->push_back(z);
}

dado::dado(int dimensions, QVector<double> coordenadas)
{
    this->dimensions=dimensions;
    vec = new QVector<double>(coordenadas);

}

double dado::getCoord(int pos)
{
    return this->vec->at(pos);
}

int dado::getDimensions()
{
    return this->vec->count();
}

