#ifndef SEAT_H
#define SEAT_H

#include <string>
using namespace std;

class Seat {
protected:
    string seatNumber;
    bool isBooked;
    double baseMultiplier;

public:
    Seat(string num = "", double mult = 1.0)
        : seatNumber(num), isBooked(false), baseMultiplier(mult) {}

    virtual ~Seat() {}

    virtual string getSeatClass() const = 0;
    double getMultiplier() const { return baseMultiplier; }
    string getSeatNumber() const { return seatNumber; }
    bool getStatus() const { return isBooked; }

    void bookSeat() { isBooked = true; }
    void cancelSeat() { isBooked = false; }
};

class EconomySeat : public Seat {
public:
    EconomySeat(string num = "") : Seat(num, 1.0) {}
    string getSeatClass() const override { return "Economy"; }
};

class BusinessSeat : public Seat {
public:
    BusinessSeat(string num = "") : Seat(num, 1.75) {}
    string getSeatClass() const override { return "Business"; }
};

class FirstClassSeat : public Seat {
public:
    FirstClassSeat(string num = "") : Seat(num, 2.5) {}
    string getSeatClass() const override { return "First Class"; }
};

#endif