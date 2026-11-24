#ifndef TICKETING_H
#define TICKETING_H
#include <iostream>
#include <string>
using namespace std;

class Ticket {
private:
    string ticketNumber;
    string pnrCode;
    string passengerName;
    double amountPaid;
    bool isIssued;

public:
    Ticket() : ticketNumber("TKT-0000"), pnrCode("XXXXXX"), passengerName("Unknown"), amountPaid(0.0), isIssued(false) {}
    Ticket(string tNum, string pnr, string name, double amount)
        : ticketNumber(tNum), pnrCode(pnr), passengerName(name), isIssued(true) {
        setAmountPaid(amount);
    }

    // Getters
    string getTicketNumber() const { return ticketNumber; }
    string getPnrCode() const { return pnrCode; }
    string getPassengerName() const { return passengerName; }
    double getAmountPaid() const { return amountPaid; }
    bool getIssueStatus() const { return isIssued; }

    // Setters with Validation
    void setAmountPaid(double amount) { amountPaid = (amount >= 0) ? amount : 0.0; }
    void voidTicket() { isIssued = false; }

    void displayTicket() const {
        cout << "Ticket: " << ticketNumber << " (PNR: " << pnrCode << ") | Passenger: " << passengerName
             << " | Paid: PKR " << amountPaid << " | Status: " << (isIssued ? "Issued" : "Void") << endl;
    }
};

class BoardingPass {
private:
    string passID;
    string passengerName;
    string gateNumber;
    string boardingTime;
    bool isBoarded;

public:
    BoardingPass() : passID("BP-000"), passengerName("Unknown"), gateNumber("G-00"), boardingTime("00:00"), isBoarded(false) {}
    BoardingPass(string id, string name, string gate, string bTime)
        : passID(id), passengerName(name), gateNumber(gate), boardingTime(bTime), isBoarded(false) {}

    // Getters
    string getPassID() const { return passID; }
    string getGateNumber() const { return gateNumber; }
    string getBoardingTime() const { return boardingTime; }
    bool getBoardedStatus() const { return isBoarded; }

    // Setters with Validation
    void setGateNumber(string gate) { if (!gate.empty()) gateNumber = gate; }
    void setBoardingTime(string bTime) { if (!bTime.empty()) boardingTime = bTime; }
    void markBoarded() { isBoarded = true; }

    void displayBoardingPass() const {
        cout << "Boarding Pass [" << passID << "] | Passenger: " << passengerName
             << " | Gate: " << gateNumber << " | Boarding: " << boardingTime
             << " | Boarded: " << (isBoarded ? "Yes" : "No") << endl;
    }
};

class BaggageTag {
private:
    string tagID;
    string passengerName;
    double weightKg;
    double extraFee;

public:
    BaggageTag() : tagID("BAG-000"), passengerName("Unknown"), weightKg(0.0), extraFee(0.0) {}
    BaggageTag(string id, string name, double weight) : tagID(id), passengerName(name) {
        setWeightKg(weight);
    }

    // Getters
    string getTagID() const { return tagID; }
    double getWeightKg() const { return weightKg; }
    double getExtraFee() const { return extraFee; }

    // Setters with Validation (20kg free allowance, PKR 500/kg extra)
    void setWeightKg(double weight) {
        weightKg = (weight >= 0) ? weight : 0.0;
        extraFee = (weightKg > 20.0) ? (weightKg - 20.0) * 500.0 : 0.0;
    }

    void displayBaggageTag() const {
        cout << "Baggage Tag [" << tagID << "] | Passenger: " << passengerName
             << " | Weight: " << weightKg << " kg | Extra Fee: PKR " << extraFee << endl;
    }
};
#endif
