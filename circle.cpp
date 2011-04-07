/* 
 * File:   Circle.cpp
 * Author: Isma
 * 
 * Created on 5 de Abril de 2011, 21:46
 */

#include "circle.h"
#include "classifier.h"
#include "euclidiandistance.h"
#include <math.h>

Circle::Circle(double x1, double y1, double x2, double y2, double x3, double y3){
    this->calculateCircleEquation(x1,y1,x2,y2,x3,y3);
}

Circle::Circle(const Datum * a, const Datum * b, const Datum * c){
    this->calculateCircleEquation(a->x(),a->y(),b->x(),b->y(),c->x(),c->y());
}

void Circle::calculateCircleEquation(double x1, double y1, double x2, double y2, double x3, double y3){
    int a,b, C, A, W, h, r;

    A = (x1*x1-x2*x2+y1*y1-y2*y2)/(x1-x2);
    C = x1*x1-x3*x3+y1*y1-y3*y3;
    W = ((y1-y3)*(x1-x2)-(y2-y1)*(x3-x1))/(x1-x2);
    h = (C+A*(x3-x1))/W;
    b = h/2;

    a = (x1*x1-x2*x2+y1*y1-y2*y2+h*(y2-y1))/(2*(x1-x2));

    r = sqrt((x1-a)*(x1-a)+(y1-b)*(y1-b));

    center = Datum(a, b);
    this->radius = r;
}

Circle::Circle(const Datum & c, double r){
    center = c;
    radius = r;
}

bool Circle::internalPoint(const Datum * d) const{
    return (new EuclidianDistance())->distance(&center, d) <= radius;
}


Circle::Circle(const Circle& orig) {
}

Circle::~Circle() {
}

const Datum & Circle::getCenter() const
{
    return center;
}

const double & Circle::getRadius() const
{
    return radius;
}

