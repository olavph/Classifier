#include "ibl1.h"

IBL1::IBL1()
{
}

void IBL1::train(const QVector<Datum *> trainSet, const DistanceCalculation * dc)
{
    _conceptualDescriptor.clear();
    _incorrectlyClassifiedData.clear();
    foreach (Datum * underTraining, trainSet) {
        Datum * mostSimilar = NULL;
        double greaterSimilarity = INT_MIN;
        foreach (Datum * added, _conceptualDescriptor) {
            double currentSimilarity = similarity(underTraining, added, dc);
            if (currentSimilarity > greaterSimilarity) {
                mostSimilar = added;
                greaterSimilarity = currentSimilarity;
            }
        }
        if (mostSimilar == NULL ? true : underTraining->myOwnSuperSecretClass != mostSimilar->myOwnSuperSecretClass) {
            _incorrectlyClassifiedData.append(underTraining);
        }
        _conceptualDescriptor.append(underTraining);
    }
}
