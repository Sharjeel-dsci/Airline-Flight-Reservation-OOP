#ifndef FLIGHTSCHEDULE_H
#define FLIGHTSCHEDULE_H
#include <iostream>
#include <string>
using namespace std;

class FlightSchedule {
private:
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
public:
    FlightSchedule(string fNum, string orig, string dest, string time)
        : flightNumber(fNum), origin(orig), destination(dest), departureTime(time) {}
    void displaySchedule() const {
        cout << "Flight: " << flightNumber << " | " << origin << " -> " << destination << " | Departure: " << departureTime << endl;
    }
};
#endif
