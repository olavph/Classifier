#ifndef CLASS_H
#define CLASS_H

#include "QColor"

class Class
{
public:
    Class(){};
    Class(QColor color, QString name);
    QColor getColor() const;
    QString getName() const;
    bool operator <(Class other) const;

private:
    QColor color;
    QString name;
};

#endif // CLASS_H
