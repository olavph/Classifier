/* 
 * File:   Triple.cpp
 * Author: Isma
 * 
 * Created on 5 de Abril de 2011, 22:49
 */

#include <signal.h>

#include "triple.h"
#include "datum.h"
#include "line.h"
#include "math.h"

Triple::Triple(const Datum * a, const Datum * b, const Datum * c) {
    this->a = a;
    this->b = b;
    this->c = c;

    this->centroid_ = this->centroid();
}

Triple::Triple(const Triple& orig) {
}

Triple::~Triple() {
}

const Datum * Triple::getA(){
    return this->a;
}

const Datum * Triple::getB(){
    return this->b;
}

const Datum * Triple::getC(){
    return this->c;
}

Datum Triple::medianPointAtSegment(const Datum * a, const Datum * b){
    return Datum((a->x()+b->x())/2, (a->y()+b->y())/2);
}

Datum Triple::medianPointAB(){
    return this->medianPointAtSegment(this->a, this->b);
}

Datum Triple::medianPointAC(){
    return this->medianPointAtSegment(this->a, this->c);
}


Datum Triple::medianPointBC(){
    return this->medianPointAtSegment(this->b, this->c);
}

Datum Triple::centroid(){
//    Line lineForAB(*this->a, *this->b);
//    Line lineForAC(*this->a, *this->c);
//    Datum result = lineForAB.intersection(lineForAC);
//    return result;
    //TODO return that?
    return circumcircle().getCenter();
}

Circle Triple::circumcircle()
{
    return Circle(a, b, c);
}

const QSet<Triple*> Triple::getNeighbors() const
{
    return neighbors;
}

bool Triple::isBorder() const{
    return this->neighbors.size() < 3;
}

bool Triple::isNeighbor(Triple * other){
    size_t count = 0;
    if ((this->a == other->a) || (this->a == other->b) || (this->a == other->c))
        count++;
    if ((this->b == other->a) || (this->b == other->b) || (this->b == other->c))
        count++;
    if ((this->c == other->a) || (this->c == other->b) || (this->c == other->c))
        count++;
    return count == 2;
}

void Triple::findNeighbors(const QSet<Triple*> & others)
{
    foreach (Triple * other, others)
        if (isNeighbor(other))
            neighbors.insert(other);
}

bool Triple::containsPoint(const Datum* datum) const{
    return datum == this->a || datum == this->b || datum == this->c;
}

Datum Triple::uniqueNoBorderPoint(){
    const Datum *opositeVertex;
    Triple * neighborA = *neighbors.begin();
    Triple * neighborB = *(neighbors.begin() + 1);
    if (neighborA->containsPoint(this->a) && neighborB->containsPoint(this->a)){
        opositeVertex = this->a;
    }else{
        if (neighborA->containsPoint(this->b) && neighborB->containsPoint(this->b)){
            opositeVertex = this->b;
        }else{
            opositeVertex = this->c;
        }
    }

    return Datum(opositeVertex->x(),opositeVertex->y());

}

Datum Triple::medianPointAtBorderEdge(){
    const Datum *opositeVertex;
    Triple * neighborA = *neighbors.begin();
    Triple * neighborB = *(neighbors.begin() + 1);
    if (neighborA->containsPoint(this->a) && neighborB->containsPoint(this->a)){
        return medianPointBC();
    }else{
        if (neighborA->containsPoint(this->b) && neighborB->containsPoint(this->b)){
            return medianPointAC();
        }else{
            return medianPointAB();
        }
    }

    return Datum(opositeVertex->x(),opositeVertex->y());
}

double Triple::cosenoVec(const Datum * datum){
    double voltaX, voltaY;
    voltaX = datum->x();
    voltaY = datum->y();
    double nX1, nX2, nY1, nY2;
    if(datum == this->a){
        nX1 = this->b->x()-voltaX;
        nX2 = this->c->x()-voltaX;
        nY1 = this->b->y()-voltaY;
        nY2 = this->c->y()-voltaY;
    }
    else{
        if (datum == this->b){
            nX1 = this->a->x()-voltaX;
            nX2 = this->c->x()-voltaX;
            nY1 = this->a->y()-voltaY;
            nY2 = this->c->y()-voltaY;
        }else{
            nX1 = this->b->x()-voltaX;
            nX2 = this->a->x()-voltaX;
            nY1 = this->b->y()-voltaY;
            nY2 = this->a->y()-voltaY;
        }
    }
    return nX1*nX2+nY1*nY2/sqrt(nX1*nX1+nY1*nY1)*sqrt(nX2*nX2+nY2*nY2);

}

Datum Triple::toInfinityAndBeyondPoint(){
    const Datum *opositeVertex;
    Triple * neighborA = *neighbors.begin();
    Triple * neighborB = *(neighbors.begin() + 1);
    if (neighborA->containsPoint(this->a) && neighborB->containsPoint(this->a)){
        opositeVertex = this->a;
    }else{
        if (neighborA->containsPoint(this->b) && neighborB->containsPoint(this->b)){
            opositeVertex = this->b;
        }else{
            opositeVertex = this->c;
        }
    }

    Datum borderMedian = this->medianPointAtBorderEdge();
    double xM = borderMedian.x();
    double yM = borderMedian.y();

    Datum circleCenter = this->centroid();
    double xC = circleCenter.x();
    double yC = circleCenter.y();


    if (cosenoVec(opositeVertex) < 0){
        xM = -xM+2*xC;
        yM = -yM+2*yC;
    }

    return Datum(xM,yM);


}
