/* 
 * File:   Line.h
 * Author: Isma
 *
 * Created on 6 de Abril de 2011, 00:42
 */

#ifndef LINE_H
#define	LINE_H

#include "datum.h"

class Line {
public:
    Line();
    Line(double x1, double y1, double x2, double y2);
    Line(const Datum& a, const Datum& b);
    Line(double m, double b);
    Line(const Line& orig);
    Line perpendicular(double x, double y);
    double getM();
    double getB();
    Datum intersection(Line other);
    
    virtual ~Line();
private:
    double m;
    double b;

};

#endif	/* LINE_H */

