#include "generator.h"
#include <math.h>
#include <assert.h>

Generator::Generator()
{
}

QVector< QPair<Datum, Class> > * Generator::randomSet(unsigned int size, QRect bounds, QVector<Class> classes)
{
    QVector< QPair<Datum, Class> > * set = new QVector< QPair<Datum, Class> >();
    for(unsigned int i = 0; i < size; i++) {
        double x = bounds.x() + bounds.width() * rand();
        double y = bounds.y() + bounds.height() * rand();
        Datum datum(x, y);
        Class randomClass = classes.at((int)(classes.size() * rand()));
        set->push_back(QPair<Datum, Class>(datum, randomClass));
    }
    return set;
}

QVector<QPair<Datum, Class> > * Generator::spiral(QRect bounds, unsigned int baseRadius, unsigned int radiusIncreaseFactor, int startingAngle, unsigned int noiseMargin, Class dataClass)
{
    assert(radiusIncreaseFactor > 1);

    QVector< QPair<Datum, Class> > * set = new QVector< QPair<Datum, Class> >();
    int centerX = (bounds.width() - bounds.x()) / 2 + bounds.x();
    int centerY = (bounds.height() - bounds.y()) / 2 + bounds.y();
    unsigned int radius = baseRadius;
    int angle = startingAngle;
    while(true) {
        int noise = noiseMargin * (2 * rand() - 1);
        double x = centerX + radius * cos(angle) * noise;
        double y = centerY + radius * sin(angle) * noise;
        if (!bounds.contains(x, y))
            break;
        Datum datum(x, y);
        set->push_back(QPair<Datum, Class>(datum, dataClass));

        radius *= radiusIncreaseFactor;
        angle += 10; //TODO parameterize
    }
    return set;
}
