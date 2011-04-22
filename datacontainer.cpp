#include "datacontainer.h"
#include "circle.h"

DataContainer::DataContainer()
{
}

void DataContainer::addDatum(Datum * datum)
{
    points.append(datum);
}

void DataContainer::addData(QVector<Datum*> & data)
{
    points += data;
}

const QVector<Datum*> & DataContainer::getData() const
{
    return points;
}

void DataContainer::clearData()
{
    points.clear();
}

const QVector<Triple*> DataContainer::getTriples()
{
    // Creates list of triples without internal points (Delaunay Triangulation)

    QVector<Triple*> triplesList;
    int numPoints = points.size();

    for (int a = 0; a < numPoints; a++) {
        for (int b = a+1; b < numPoints; b++) {
            for (int c = b+1; c < numPoints; c++) {
                Triple * aTriple = new Triple(points.at(a),points.at(b),points.at(c));
                triplesList.append(aTriple);
                Circle tempCircle = aTriple->circumcircle();
                for (int d = 0; d < numPoints; d++) {
                    if ((a != d) && (b != d) && (c != d)){
                        if (tempCircle.internalPoint(points.at(d))) {
                            triplesList.pop_back();
                            delete aTriple;
                            break;
                        }
                    }
                }
            }
        }
    }

    // Finds neighbors to draw Voronoi Diagram

    for (int i = 0; i < triplesList.size(); i++) {
        triplesList.at(i)->findNeighbors(triplesList);
    }

    return triplesList;
}
