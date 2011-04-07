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
    //ordenar todos os pontos em triplas

    QVector<Triple*> triplesList;

    int numPoints = points.size();


    for (int a = 0; a < numPoints; a++) {
        for (int b = 0; b < numPoints; b++) {
            if(a != b)
                for (int c = 0; c < numPoints; c++) {
                    if ((a != c) && (b != c)){
                        triplesList.push_back(new Triple(points.at(a),points.at(b),points.at(c)));
                    }
                }
        }
    }


    //Verifica a existencia de triplas sem nenhum outro ponto interno;
    QVector<Triple*> triplesWithoutOtherInternalPoints;
    Circle * tempCircle;
    bool add = true;
    for (int i = 0; i < triplesList.size(); i++) {
        Triple * aTriple = triplesList.at(i);
        tempCircle = new Circle(*aTriple->getA(), *aTriple->getB(), *aTriple->getC());
        for (int h = 0; h < numPoints; h++) {
            if (tempCircle->internalPoint(points.at(h)->x(),(points.at(h)->y()))) {
                add = false;
                break;
            }
        }
        if (add){
            triplesWithoutOtherInternalPoints.push_back(aTriple);
        }else{
            add = true;
        }
    }


    //Classifica vizinhos, para desenhar linhas entre os centros dos circulos vizinhos;
//    QVector< pair <Triple*, Triple*>* > * neighbours = new vector< pair <Triple*, Triple*>* >();
//    pair<Triple*, Triple*> * tempPair;
//    for (size_t c = 0; c < triplesWithoutOtherInternalPoints->size(); c++) { //c++!!!!!
//        for (size_t d = 0; d < triplesWithoutOtherInternalPoints->size(); d++) {
//            if (triplesWithoutOtherInternalPoints->at(c)->isNeighbor(triplesWithoutOtherInternalPoints->at(d))){
//                tempPair = new pair<Triple*, Triple*>(triplesWithoutOtherInternalPoints->at(c), triplesWithoutOtherInternalPoints->at(d));
//                neighbours->push_back(tempPair);
//            }
//        }
//    }

    return triplesWithoutOtherInternalPoints;
}

