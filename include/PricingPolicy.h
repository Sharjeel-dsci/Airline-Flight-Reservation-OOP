#ifndef PRICINGPOLICY_H
#define PRICINGPOLICY_H
#include <iostream>
#include <string>
using namespace std;

class PricingPolicy {
private:
    string cabinClass;
    double baseFare;
public:
    PricingPolicy(string cClass, double fare) : cabinClass(cClass), baseFare(fare) {}
    void displayFare() const {
        cout << "Cabin Class: " << cabinClass << " | Ticket Fare: PKR " << baseFare << endl;
    }
};
#endif
