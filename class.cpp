#include "class.h"

Class::Class(QColor color, QString name)
{
    this->color = color;
    this->name = name;
}

QColor Class::getColor() const
{
    return color;
}

QString Class::getName() const
{
    return name;
}

bool Class::operator <(Class other) const
{
    return name < other.getName();
}
