#ifndef PRICING_POLICY_H
#define PRICING_POLICY_H

#include <string>
using namespace std;

class PricingPolicy {
private:
    double businessMultiplier;
    double highDemandThreshold;
    double highDemandSurge;
    double moderateDemandThreshold;
    double moderateDemandSurge;
    double taxRate;

public:
    PricingPolicy()
        : businessMultiplier(1.8),
          highDemandThreshold(0.85),
          highDemandSurge(1.25),
          moderateDemandThreshold(0.70),
          moderateDemandSurge(1.15),
          taxRate(0.05) {}

    void setBusinessMultiplier(double mult) {
        if (mult >= 1.0) businessMultiplier = mult;
    }

    void setTaxRate(double rate) {
        if (rate >= 0.0 && rate <= 1.0) taxRate = rate;
    }

    void setDemandThresholds(double modThresh, double highThresh) {
        if (modThresh > 0.0 && highThresh > modThresh && highThresh <= 1.0) {
            moderateDemandThreshold = modThresh;
            highDemandThreshold = highThresh;
        }
    }

    double getBusinessMultiplier() const { return businessMultiplier; }
    double getTaxRate() const { return taxRate; }

    double getDemandMultiplier(double occupancyRate) const {
        if (occupancyRate >= highDemandThreshold) return highDemandSurge;
        if (occupancyRate >= moderateDemandThreshold) return moderateDemandSurge;
        return 1.0;
    }

    double calculateFinalFare(double baseFare, double occupancyRate, const string& seatClass) const {
        if (baseFare < 0.0) return 0.0;

        double classFare = baseFare;
        if (seatClass == "Business" || seatClass == "business") {
            classFare = baseFare * businessMultiplier;
        }

        double demandAdjustedFare = classFare * getDemandMultiplier(occupancyRate);
        double totalWithTax = demandAdjustedFare * (1.0 + taxRate);

        return totalWithTax;
    }
};

#endif 