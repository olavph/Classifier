#include "ibl/ibl2.h"

IBL2::IBL2()
{
}

void IBL2::train(const QVector<Datum *> trainSet, const DistanceCalculation * dc)
{
    foreach (Datum * underTraining, trainSet) {
        Datum * mostSimilar = NULL;
        double greaterSimilarity = INT_MIN;
        foreach (Datum * added, _conceptualDescriptor) {
            double currentSimilarity = -dc->distance(underTraining, added);
            if (currentSimilarity > greaterSimilarity) {
                mostSimilar = added;
                greaterSimilarity = currentSimilarity;
            }
        }
        if (mostSimilar == NULL ? true : underTraining->myOwnSuperSecretClass != mostSimilar->myOwnSuperSecretClass) {
            _incorrectlyClassifiedData.append(underTraining);
            _conceptualDescriptor.append(underTraining);
        }
    }
}