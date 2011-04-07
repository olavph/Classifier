#include "generator.h"
#include <math.h>
#include <assert.h>

Generator::Generator()
{
}

QVector<Datum*> Generator::randomSet(unsigned int size, QRect bounds, QVector<Class*> classes)
{
    QVector<Datum*> set;

    for(unsigned int i = 0; i < size; i++) {
        double x = bounds.x() + bounds.width() * floatRand();
        double y = bounds.y() + bounds.height() * floatRand();
        Class * randomClass = classes.at((int)(classes.size() * floatRand()));
        Datum * datum = new Datum(x, y, randomClass);
        set.push_back(datum);
    }
    return set;
}

QVector<Datum*> Generator::spiral(QRect bounds, double baseRadius, double radiusIncreaseFactor, double startingAngle, double noiseMargin, Class * dataClass)
{
    assert(radiusIncreaseFactor > 1);

    QVector<Datum*> set;
    double centerX = (bounds.width() - bounds.x()) / 2 + bounds.x();
    double centerY = (bounds.height() - bounds.y()) / 2 + bounds.y();
    double radius = baseRadius;
    double angle = startingAngle * M_PI/180;
    while(true) {
        double noise = noiseMargin * (2 * floatRand() - 1);
        double x = centerX + (radius + noise) * cos(angle);
        double y = centerY + (radius + noise) * sin(angle);
        if (!bounds.contains(x, y))
            break;
        Datum * datum = new Datum(x, y, dataClass);
        set.push_back(datum);

        radius *= 1 + (radiusIncreaseFactor - 1) / (360 / 10);
        angle += 10 * M_PI/180; //TODO parameterize
    }
    return set;
}

QVector<Datum*> Generator::doubleSpiral(QRect bounds, double baseRadius, double radiusIncreaseFactor, double startingAngle, double noiseMargin, Class * class1, Class * class2)
{
    QVector<Datum*> set1 = spiral(bounds, baseRadius, radiusIncreaseFactor, startingAngle, noiseMargin, class1);
    QVector<Datum*> set2 = spiral(bounds, baseRadius, radiusIncreaseFactor, startingAngle + 180, noiseMargin, class2);
    return set1 + set2;
}

double Generator::floatRand()
{
    return rand()/((double)RAND_MAX + 1);
}
