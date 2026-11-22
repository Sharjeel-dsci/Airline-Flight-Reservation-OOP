#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include <string>

using namespace std;

class Seat {
private:
    // Strictly Encapsulated Data Members
    string seatNumber;
    string seatClass; // Economy, Business, or First Class
    double baseMultiplier;
    bool isBooked;

    // Private helper to set multiplier based on class
    void updateMultiplier() {
        if (seatClass == "First Class") {
            baseMultiplier = 2.5;
        } else if (seatClass == "Business") {
            baseMultiplier = 1.75;
        } else {
            baseMultiplier = 1.0;
        }
    }

public:
    Seat() : seatNumber("0A"), seatClass("Economy"), baseMultiplier(1.0), isBooked(false) {}

    Seat(string sNum, string sClass, bool booked = false) {
        setSeatNumber(sNum);
        setSeatClass(sClass);
        isBooked = booked;
    }

    // Validated Setters
    void setSeatNumber(const string& sNum) {
        if (!sNum.empty()) {
            seatNumber = sNum;
        }
    }

    void setSeatClass(const string& sClass) {
        if (sClass == "First Class" || sClass == "first class") {
            seatClass = "First Class";
        } else if (sClass == "Business" || sClass == "business") {
            seatClass = "Business";
        } else {
            seatClass = "Economy";
        }
        updateMultiplier();
    }

    // Read-Only Getters
    string getSeatNumber() const { return seatNumber; }
    string getSeatClass() const { return seatClass; }
    double getMultiplier() const { return baseMultiplier; }
    bool getStatus() const { return isBooked; }

    // Controlled State Modifiers
    bool bookSeat() {
        if (!isBooked) {
            isBooked = true;
            return true;
        }
        return false;
    }

    void cancelSeat() {
        isBooked = false;
    }
};

class Passenger {
private:
    string passengerID;
    string fullName;

public:
    Passenger() {}

    Passenger(string id, string name) {
        setPassengerID(id);
        setFullName(name);
    }

    void setPassengerID(const string& id) {
        if (!id.empty()) {
            passengerID = id;
        }
    }

    void setFullName(const string& name) {
        if (!name.empty()) {
            fullName = name;
        }
    }

    string getPassengerID() const { return passengerID; }
    string getFullName() const { return fullName; }
};

#endif // SEAT_H