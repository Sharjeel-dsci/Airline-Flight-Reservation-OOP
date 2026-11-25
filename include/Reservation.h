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
    string seatNumber;
    string status;

public:
    Reservation() : reservationID(0), passengerName("Unknown"), flightNumber("N/A"), seatNumber("00X"), status("Pending") {}
    Reservation(int id, string name, string flight, string seat)
        : reservationID(id), passengerName(name), flightNumber(flight), seatNumber(seat), status("Confirmed") {}

    // Getters
    int getReservationID() const { return reservationID; }
    string getPassengerName() const { return passengerName; }
    string getFlightNumber() const { return flightNumber; }
    string getSeatNumber() const { return seatNumber; }
    string getStatus() const { return status; }

    // Setters with Validation
    void setFlightNumber(string flight) { if (!flight.empty()) flightNumber = flight; }
    void setSeatNumber(string seat) { if (!seat.empty()) seatNumber = seat; }
    void confirmReservation() { status = "Confirmed"; }
    void cancelReservation() { status = "Cancelled"; }

    void displayReservation() const {
        cout << "Reservation #" << reservationID << " | Passenger: " << passengerName
             << " | Flight: " << flightNumber << " | Seat: " << seatNumber
             << " | Status: " << status << endl;
    }
};
#endif
