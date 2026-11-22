#ifndef LOYALTY_H
#define LOYALTY_H
#include <iostream>
#include <string>
using namespace std;

class LoyaltyAccount {
private:
    string memberID;
    string memberName;
    int points;
public:
    LoyaltyAccount(string id, string name, int pts) : memberID(id), memberName(name), points(pts) {}
    void addPoints(int pts) { points += pts; }
    void displayLoyalty() const {
        cout << "Loyalty ID: " << memberID << " | Member: " << memberName << " | Points: " << points << endl;
    }
};
#endif
