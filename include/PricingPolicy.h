#ifndef PRICINGPOLICY_H
#define PRICINGPOLICY_H
#include <iostream>
#include <string>
using namespace std;

class PricingPolicy {
private:
    string cabinClass;
    double baseFare;
    double taxPercent;

public:
    PricingPolicy() : cabinClass("Economy"), baseFare(10000.0), taxPercent(15.0) {}
    PricingPolicy(string cClass, double fare, double tax) : cabinClass(cClass) {
        setBaseFare(fare);
        setTaxPercent(tax);
    }

    // Getters
    string getCabinClass() const { return cabinClass; }
    double getBaseFare() const { return baseFare; }
    double getTaxPercent() const { return taxPercent; }

    // Setters with Validation
    void setCabinClass(string cClass) { if (!cClass.empty()) cabinClass = cClass; }
    void setBaseFare(double fare) { baseFare = (fare > 0) ? fare : 5000.0; }
    void setTaxPercent(double tax) { taxPercent = (tax >= 0 && tax <= 100) ? tax : 15.0; }

    double calculateTotalFare() const {
        return baseFare + (baseFare * taxPercent / 100.0);
    }

    void displayFare() const {
        cout << "Cabin Class: " << cabinClass << " | Base Fare: PKR " << baseFare
             << " | Tax: " << taxPercent << "% | Total Fare: PKR " << calculateTotalFare() << endl;
    }
};
#endif
