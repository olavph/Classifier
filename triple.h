/* 
 * File:   Triple.h
 * Author: Isma
 *
 * Created on 5 de Abril de 2011, 22:49
 */

#include "datum.h"
#include "circle.h"

#ifndef TRIPLE_H
#define	TRIPLE_H

class Triple {
public:
    Triple(){};
    Triple(const Datum * a, const Datum * b, const Datum * c);
    Triple(const Triple& orig);
    Datum medianPointAB();
    Datum medianPointAC();
    Datum medianPointBC();
    const Datum * getA();
    const Datum * getB();
    const Datum * getC();
    Datum centroid();
    Circle excircle();
    bool isNeighbor(Triple* other);
    virtual ~Triple();
private:
    Datum medianPointAtSegment(const Datum * a, const Datum * b);
protected:
    const Datum * a;
    const Datum * b;
    const Datum * c;
    Datum centroid_;

};

#endif	/* TRIPLE_H */

