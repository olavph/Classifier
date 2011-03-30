#include "classifier.h"
#include <math.h>

Classifier::Classifier()
{


}

double Classifier::manhattan(Datum d1, Datum d2)
{
    double manhattanDistance = 0;
    if (d1.getDimensions() != d2.getDimensions()){
        return -1;
    }
    for(unsigned int i = 0; i < d1.getDimensions(); i++){
        manhattanDistance += fabs(d1.getCoordinate(i) - d2.getCoordinate(i));
    }
    return manhattanDistance;
}

double Classifier::euclidian(Datum d1, Datum d2)
{
    double euclidianDistance = 0;
    if (d1.getDimensions() != d2.getDimensions()){
        return -1;
    }
    for(unsigned int i = 0; i < d1.getDimensions(); i++){
        euclidianDistance += fabs(pow((d1.getCoordinate(i) - d2.getCoordinate(i)),2.0));
    }
    return sqrt(euclidianDistance);
}

//Class Classifier::nN(Datum d)       ERRRRRRRROOOOOO!!!!!!!!!!!!
//{
//    pair<Datum, Class> nearestNeighbour = this->classifiedData().at(0);
//    pair<Datum, Class> data = this->classifiedData().at(1);
//    for(size_t i = 2; i <= this->classifiedData().size(); i++){
//           if(euclidian(nearestNeighbour.first, d) < euclidian(data.first, d))
//           {
//                nearestNeighbour = data;
//           }
//           data = this->classifiedData().at(i);
//    }
//    return nearestNeighbour.second;
//}


