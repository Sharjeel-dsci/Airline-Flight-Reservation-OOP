#ifndef SEAT_H
#define SEAT_H
#include <iostream>
#include <string>
using namespace std;

class Seat {
private:
    string seatNumber;
    string seatClass;
    bool isBooked;
public:
    Seat(string num, string sClass) : seatNumber(num), seatClass(sClass), isBooked(false) {}
    void bookSeat() { isBooked = true; }
    void displaySeat() const {
        cout << "Seat: " << seatNumber << " (" << seatClass << ") - Status: " << (isBooked ? "Booked" : "Available") << endl;
    }
};
#endif
