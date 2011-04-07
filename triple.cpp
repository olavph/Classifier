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
    Line lineForAB(*this->a, *this->b);
    Line lineForAC(*this->a, *this->c);
    Datum result = lineForAB.intersection(lineForAC);
    qDebug("(%f, %f)", result.x(), result.y());
    return result;
}

bool Triple::isNeighbor(Triple* other){
    size_t count = 0;
    if ((this->a == other->a) || (this->a == other->b) || (this->a == other->c))
        count++;
    if ((this->b == other->a) || (this->b == other->b) || (this->b == other->c))
        count++;
    if ((this->c == other->a) || (this->c == other->b) || (this->c == other->c))
        count++;
    return count == 2;
}
