#include "ibl3.h"
#include <math.h>

IBL3::IBL3()
{
}

void IBL3::train(const QSet<Datum*> trainSet, const DistanceCalculation *dc)
{
    _conceptualDescriptor.clear();
    _incorrectlyClassifiedData.clear();
    foreach (Datum * underTraining, trainSet) {
        // Creates precision and frequency intervals for datum under training and its class
        precisionIntervals[underTraining] = ClassificationRecord(PRECISION_INTERVAL_Z);
        precisionIntervals[underTraining].incrementCorrects();
        if (!frequencyIntervals.contains(underTraining->myOwnSuperSecretClass)) {
            frequencyIntervals[underTraining->myOwnSuperSecretClass] = ClassificationRecord(FREQUENCY_INTERVAL_Z);
        }
        frequencyIntervals[underTraining->myOwnSuperSecretClass].incrementCorrects();
        foreach (ClassificationRecord record, frequencyIntervals.values()) {
            record.incrementIncorrects();
        }

        // If conceptual descriptor is empty, there is nothing to compare it with
        if (_conceptualDescriptor.empty()) {
            _conceptualDescriptor.insert(underTraining);
            continue;
        }

        Datum * mostSimilar = NULL;
        double greaterSimilarity = INT_MIN;
        QHash<Datum*, double> similarities;
        foreach (Datum * added, _conceptualDescriptor) {
            double currentSimilarity = similarity(underTraining, added, dc);
            if (currentSimilarity >= greaterSimilarity) {
                if (acceptable(added)) {
                    mostSimilar = added;
                    greaterSimilarity = currentSimilarity;
                }
                // Only those that are equally or more similar than the chosen one may be rejected
                similarities[added] = currentSimilarity;
            }
        }
        // Remove most similar so it may not be marked as incorrect twice
        similarities.remove(mostSimilar);

        // Selects random datum if there is no acceptable one
        if (mostSimilar == NULL) {
            int randomIndex = ((double)rand())/RAND_MAX * _conceptualDescriptor.size();
            mostSimilar = *(_conceptualDescriptor.begin() + randomIndex);
        }

        // Updates precision and frequency intervals
        if (underTraining->myOwnSuperSecretClass == mostSimilar->myOwnSuperSecretClass) {
            precisionIntervals[mostSimilar].incrementCorrects();
        } else {
            precisionIntervals[mostSimilar].incrementIncorrects();
            _incorrectlyClassifiedData.insert(underTraining);
            _conceptualDescriptor.insert(underTraining);
        }

        foreach (Datum * added, _conceptualDescriptor) {
            if (similarities.contains(added) && similarities[added] >= greaterSimilarity) {
                precisionIntervals[added].incrementCorrects();
                if (rejectable(added)) {
                    _conceptualDescriptor.remove(added);
                    precisionIntervals.remove(added);
                }
            }
        }
    }
}

bool IBL3::acceptable(const Datum * d) const
{
    return precisionIntervals[d].lowerLimit() > frequencyIntervals[d->myOwnSuperSecretClass].upperLimit();
}

bool IBL3::rejectable(const Datum * d) const
{
    return precisionIntervals[d].upperLimit() < frequencyIntervals[d->myOwnSuperSecretClass].lowerLimit();
}
