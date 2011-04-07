/* 
 * File:   Circle.h
 * Author: Isma
 *
 * Created on 5 de Abril de 2011, 21:46
 */

#ifndef CIRCLE_H
#define	CIRCLE_H

#include "datum.h"


class Circle {
public:
    Circle(double x1, double y1, double x2, double y2, double x3, double y3);
    Circle(const Datum& a, const Datum& b, const Datum& c);
    Circle(double xc, double yc, double r);
    Circle(const Circle& orig);

    bool internalPoint(double x, double y);

    virtual ~Circle();
private:
    void calculateCircleEquation(double x1, double y1, double x2, double y2, double x3, double y3);

    double xCenter;
    double yCenter;
    double radius;

};

#endif	/* CIRCLE_H */

