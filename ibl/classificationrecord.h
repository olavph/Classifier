#ifndef CLASSIFICATIONRECORD_H
#define CLASSIFICATIONRECORD_H

class ClassificationRecord
{
private:
    double z;
    unsigned int corrects;
    unsigned int incorrects;
public:
    ClassificationRecord();
    ClassificationRecord(double z);
    void incrementCorrects();
    void incrementIncorrects();
    double lowerLimit() const;
    double upperLimit() const;
};

#endif // CLASSIFICATIONRECORD_H
