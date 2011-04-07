#ifndef DATACONTAINER_H
#define DATACONTAINER_H7

#include <QVector>

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
};

#endif // DATACONTAINER_H
