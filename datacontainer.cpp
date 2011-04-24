#include "datacontainer.h"
#include "circle.h"

DataContainer::DataContainer()
{
}

void DataContainer::addDatum(Datum * datum)
{
    points.insert(datum);
}

void DataContainer::addData(QSet<Datum*> & data)
{
    points += data;
}

const QSet<Datum*> & DataContainer::getData() const
{
    return points;
}

void DataContainer::clearData()
{
    points.clear();
}

const QSet<Triple*> DataContainer::getTriples()
{
    // Creates list of triples without internal points (Delaunay Triangulation)

    QSet<Triple*> triplesList;

    foreach (Datum * d1, points) {
        foreach (Datum * d2, points) {
            if (d1 != d2) {
                foreach (Datum * d3, points) {
                    if ((d1 != d3) && (d2 != d3)) {
                        Triple * aTriple = new Triple(d1, d2 , d3);
                        Circle tempCircle = aTriple->circumcircle();
                        foreach (Datum * d4, points) {
                            if ((d1 != d4) && (d2 != d4) && (d3 != d4)) {
                                if (tempCircle.internalPoint(d4)) {
                                    delete aTriple;
                                    aTriple = NULL;
                                    break;
                                }
                            }
                        }
                        if (aTriple != NULL)
                            triplesList.insert(aTriple);
                    }
                }
            }
        }
    }

    // Finds neighbors to draw Voronoi Diagram

    foreach (Triple * t, triplesList)
        t->findNeighbors(triplesList);

    return triplesList;
}
