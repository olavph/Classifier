#ifndef DATACONTAINER_H
#define DATACONTAINER_H7

#include <QVector>
#include <QPair>

#include "datum.h"
#include "triple.h"

class DataContainer
{
private:
    QVector<Datum*> points;
public:
    DataContainer();
    void addDatum(Datum * datum);
    void addData(QVector<Datum*> & data);
    const QVector<Datum*> & getData() const;
    void clearData();

    const QVector<Triple*> getTriples();
    const QVector< QPair<Triple*, Triple*> > getNeighbours();
};

#endif // DATACONTAINER_H
