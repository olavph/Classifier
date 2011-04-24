#ifndef DATACONTAINER_H
#define DATACONTAINER_H7

#include <QSet>
#include <QPair>

#include "datum.h"
#include "triple.h"

class DataContainer
{
private:
    QSet<Datum*> points;
public:
    DataContainer();
    void addDatum(Datum * datum);
    void addData(QSet<Datum*> & data);
    const QSet<Datum*> & getData() const;
    void clearData();

    const QSet<Triple*> getTriples();
    const QSet< QPair<Triple*, Triple*> > getNeighbours();
};

#endif // DATACONTAINER_H
