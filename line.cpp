/* 
 * File:   Line.cpp
 * Author: Isma
 * 
 * Created on 6 de Abril de 2011, 00:42
 */

#include <math.h>

#include "line.h"

Line::Line() {
}

Line::Line(double x1, double y1, double x2, double y2){
    this->m = (y2-y1)/(x2-x1);
    this->b = y1-m*x1;
}

Line::Line(double m, double b){
    this->m = m;
    this->b = b;
}

Line::Line(const Datum& a, const Datum& b){
    this->m = (a.y()-b.y())/(a.x()-b.x());
    this->b = a.y()-m*a.x();
}

Line Line::perpendicular(double x, double y){
    double newM = -1/m;
    double b = -newM*x+y;
    return Line(newM, b);
}

Datum Line::intersection(Line other){
    double x, y;
    x = (this->b-other.getB())/(other.getM()-this->m);
    y = this->m*x+this->b;
    return Datum(x,y);
}

double Line::getB(){
    return this->b;
}

double Line::getM(){
    return this->m;
}

Line::Line(const Line& orig) {
}

Line::~Line() {
}

