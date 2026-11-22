#ifndef RESERVATION_H
#define RESERVATION_H
#include <iostream>
#include <string>
using namespace std;

class Reservation {
private:
    int reservationID;
    string passengerName;
    string flightNumber;
public:
    Reservation(int id, string name, string flight) : reservationID(id), passengerName(name), flightNumber(flight) {}
    void displayReservation() const {
        cout << "Reservation #" << reservationID << " | Passenger: " << passengerName << " | Flight: " << flightNumber << endl;
    }
};
#endif
