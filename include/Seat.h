#ifndef SEAT_H
#define SEAT_H
#include <iostream>
#include <string>
using namespace std;

class Passenger {
private:
    string passengerID;
    string fullName;
    string passportOrCNIC;
    int age;

public:
    Passenger() : passengerID("P-000"), fullName("Unknown"), passportOrCNIC("00000-0000000-0"), age(18) {}
    Passenger(string id, string name, string doc, int pAge) : passengerID(id), fullName(name), passportOrCNIC(doc) {
        setAge(pAge);
    }

    // Getters
    string getPassengerID() const { return passengerID; }
    string getFullName() const { return fullName; }
    string getPassportOrCNIC() const { return passportOrCNIC; }
    int getAge() const { return age; }

    // Setters with Validation
    void setFullName(string name) { if (!name.empty()) fullName = name; }
    void setPassportOrCNIC(string doc) { if (!doc.empty()) passportOrCNIC = doc; }
    void setAge(int pAge) { age = (pAge > 0 && pAge <= 120) ? pAge : 18; }

    void displayPassenger() const {
        cout << "Passenger [" << passengerID << "]: " << fullName
             << " | Doc: " << passportOrCNIC << " | Age: " << age << endl;
    }
};

class Seat {
private:
    string seatNumber;
    string seatClass;
    bool isBooked;

public:
    Seat() : seatNumber("00X"), seatClass("Economy"), isBooked(false) {}
    Seat(string num, string sClass) : seatNumber(num), isBooked(false) {
        setSeatClass(sClass);
    }

    // Getters
    string getSeatNumber() const { return seatNumber; }
    string getSeatClass() const { return seatClass; }
    bool getBookingStatus() const { return isBooked; }

    // Setters with Validation
    void setSeatNumber(string num) { if (!num.empty()) seatNumber = num; }
    void setSeatClass(string sClass) {
        if (sClass == "Economy" || sClass == "Business" || sClass == "First")
            seatClass = sClass;
        else
            seatClass = "Economy";
    }

    void bookSeat() {
        if (!isBooked) isBooked = true;
    }
    void cancelSeat() {
        if (isBooked) isBooked = false;
    }

    void displaySeat() const {
        cout << "Seat: " << seatNumber << " (" << seatClass << ") - Status: "
             << (isBooked ? "Booked" : "Available") << endl;
    }
};
#endif
