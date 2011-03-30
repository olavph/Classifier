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
    static QVector< QPair<Datum, Class> > * randomSet(unsigned int size, QRect bounds, QVector<Class> classes);
    static QVector< QPair<Datum, Class> > * spiral(QRect bounds, unsigned int baseRadius, unsigned int radiusIncreaseFactor, int startingAngle, unsigned int noiseMargin, Class dataClass);
};

#endif // GENERATOR_H
