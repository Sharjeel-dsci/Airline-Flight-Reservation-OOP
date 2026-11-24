#ifndef FLIGHTSCHEDULE_H
#define FLIGHTSCHEDULE_H
#include <iostream>
#include <string>
using namespace std;

class Aircraft {
private:
    string aircraftID;
    string model;
    int totalCapacity;

public:
    Aircraft() : aircraftID("AC-000"), model("Boeing 737"), totalCapacity(150) {}
    Aircraft(string id, string mdl, int cap) : aircraftID(id), model(mdl) {
        setTotalCapacity(cap);
    }

    // Getters
    string getAircraftID() const { return aircraftID; }
    string getModel() const { return model; }
    int getTotalCapacity() const { return totalCapacity; }

    // Setters with Validation
    void setModel(string mdl) { if (!mdl.empty()) model = mdl; }
    void setTotalCapacity(int cap) { totalCapacity = (cap > 0) ? cap : 100; }

    void displayAircraft() const {
        cout << "Aircraft [" << aircraftID << "]: " << model
             << " | Total Capacity: " << totalCapacity << " seats" << endl;
    }
};

class FlightSchedule {
private:
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    int availableSeats;

public:
    FlightSchedule() : flightNumber("PK-000"), origin("N/A"), destination("N/A"), departureTime("00:00"), availableSeats(0) {}
    FlightSchedule(string fNum, string orig, string dest, string time, int seats)
        : flightNumber(fNum), origin(orig), destination(dest), departureTime(time) {
        setAvailableSeats(seats);
    }

    // Getters
    string getFlightNumber() const { return flightNumber; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    int getAvailableSeats() const { return availableSeats; }

    // Setters with Validation
    void setDepartureTime(string time) { if (!time.empty()) departureTime = time; }
    void setAvailableSeats(int seats) { availableSeats = (seats >= 0) ? seats : 0; }
    void allocateSeat() { if (availableSeats > 0) availableSeats--; }

    void displaySchedule() const {
        cout << "Flight: " << flightNumber << " | " << origin << " -> " << destination
             << " | Departure: " << departureTime << " | Available Seats: " << availableSeats << endl;
    }
};
#endif

