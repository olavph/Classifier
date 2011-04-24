#include "ibl4.h"
#include <math.h>

IBL4::IBL4()
{
}

double max(double x, double y) {
    if (x > y)
        return x;
    else
        return y;
}

void IBL4::train(const QSet<Datum*> trainSet, const DistanceCalculation *dc)
{
    _conceptualDescriptor.clear();
    _incorrectlyClassifiedData.clear();
    foreach (Datum * underTraining, trainSet) {
        // Creates precision and frequency intervals for datum under training and its class
        precisionIntervals[underTraining] = ClassificationRecord(PRECISION_INTERVAL_Z);
        precisionIntervals[underTraining].incrementCorrects();
        if (!frequencyIntervals.contains(underTraining->myOwnSuperSecretClass)) {
            frequencyIntervals[underTraining->myOwnSuperSecretClass] = ClassificationRecord(FREQUENCY_INTERVAL_Z);
            attributeWeights[underTraining->myOwnSuperSecretClass] = QVector<double>(underTraining->getDimensions());
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

        // Update attribute weights
        double accumulatedWeigth = 0;
        double normalizedWeigth = 0;
        for (unsigned int i = 0; i < underTraining->getDimensions(); i++) {
            double difference = abs(underTraining->getCoordinate(0) - mostSimilar->getCoordinate(i));
            double lambda = max(frequencyIntervals[underTraining->myOwnSuperSecretClass].ratio(), frequencyIntervals[mostSimilar->myOwnSuperSecretClass].ratio());
            if (underTraining->myOwnSuperSecretClass == mostSimilar->myOwnSuperSecretClass) {
                accumulatedWeigth += (1 - lambda) * (1 - difference);
            } else {
                accumulatedWeigth += (1 - lambda) * difference;
            }
            normalizedWeigth += (1 - lambda);
            double updatedWeight = max(accumulatedWeigth / normalizedWeigth - 0.5, 0);
            attributeWeights[underTraining->myOwnSuperSecretClass].replace(i, updatedWeight);
        }
    }
}

int IBL4::similarity(const Datum * d1, const Datum * d2, const DistanceCalculation * dc) const
{
    return -dc->distance(d1, d2);
}

bool IBL4::acceptable(const Datum * d) const
{
    return precisionIntervals[d].lowerLimit() > frequencyIntervals[d->myOwnSuperSecretClass].upperLimit();
}

bool IBL4::rejectable(const Datum * d) const
{
    return precisionIntervals[d].upperLimit() < frequencyIntervals[d->myOwnSuperSecretClass].lowerLimit();
}
