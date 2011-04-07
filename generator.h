#ifndef GENERATOR_H
#define GENERATOR_H

#include <QVector>
#include <QPair>
#include <QRect>
#include <datum.h>
#include <class.h>

class Generator
{
public:
    Generator();
    static QVector<Datum*> randomSet(unsigned int size, QRect bounds, QVector<Class*> classes);
    static QVector<Datum*> spiral(QRect bounds, double baseRadius, double radiusIncreaseFactor, double startingAngle, double noiseMargin, Class * dataClass);
    static QVector<Datum*> doubleSpiral(QRect bounds, double baseRadius, double radiusIncreaseFactor, double startingAngle, double noiseMargin, Class * dataClass1, Class * dataClass2);
    static double floatRand();
};

#endif // GENERATOR_H
