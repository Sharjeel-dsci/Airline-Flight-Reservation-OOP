#ifndef TICKETING_H
#define TICKETING_H
#include <iostream>
#include <string>
using namespace std;

class Ticket {
private:
    string ticketNumber;
    string passengerName;
    string gateNumber;
public:
    Ticket(string tNum, string name, string gate) : ticketNumber(tNum), passengerName(name), gateNumber(gate) {}
    void displayBoardingPass() const {
        cout << "Ticket: " << ticketNumber << " | Passenger: " << passengerName << " | Boarding Gate: " << gateNumber << endl;
    }
};
#endif
