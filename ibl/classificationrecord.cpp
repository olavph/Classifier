#include "classificationrecord.h"
#include <math.h>
#include <assert.h>

ClassificationRecord::ClassificationRecord()
{
}

ClassificationRecord::ClassificationRecord(double z)
{
    assert(z >= 0 && z <= 1);
    this->z = z;
    corrects = 0;
    incorrects = 0;
}

void ClassificationRecord::incrementCorrects()
{
    corrects ++;
}

void ClassificationRecord::incrementIncorrects()
{
    incorrects ++;
}

double ClassificationRecord::total() const
{
    return corrects + incorrects;
}

double ClassificationRecord::ratio() const
{
    return corrects / total();
}

double ClassificationRecord::lowerLimit() const
{
    double n = total();
    double p = ratio();

    return (p + (z*z) / (2*n) - z * sqrt( p*(1-p) / n + (z*z) / (4*(n*n))) ) / (1 + (z*z) / n);
}

double ClassificationRecord::upperLimit() const
{
    double n = total();
    double p = ratio();

    return (p + (z*z) / (2*n) + z * sqrt( p*(1-p) / n + (z*z) / (4*(n*n))) ) / (1 + (z*z) / n);
}
