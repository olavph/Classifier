#include "ibl/ibl2.h"

IBL2::IBL2()
{
}

void IBL2::train(const QSet<Datum*> trainSet, const DistanceCalculation * dc)
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
            _incorrectlyClassifiedData.insert(underTraining);
            _conceptualDescriptor.insert(underTraining);
        }
    }
}
