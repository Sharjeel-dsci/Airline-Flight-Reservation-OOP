#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "FlightSchedule.h"
#include "Seat.h"
#include "Ticketing.h"

using namespace std;

class Reservation {
private:
    string reservationID;
    string passengerID;
    string passengerName;
    string flightNumber;
    string seatNumber;
    string seatClass;
    double farePaid;
    string status; 

public:
    Reservation() : farePaid(0.0), status("Confirmed") {}

    Reservation(string resID, string pID, string pName, string fNum,
                string sNum, string sClass, double fare, string stat = "Confirmed")
        : reservationID(resID), passengerID(pID), passengerName(pName),
          flightNumber(fNum), seatNumber(sNum), seatClass(sClass),
          farePaid(fare), status(stat) {}

    // Getters
    string getReservationID() const { return reservationID; }
    string getPassengerID() const { return passengerID; }
    string getPassengerName() const { return passengerName; }
    string getFlightNumber() const { return flightNumber; }
    string getSeatNumber() const { return seatNumber; }
    string getSeatClass() const { return seatClass; }
    double getFarePaid() const { return farePaid; }
    string getStatus() const { return status; }

    void cancel() {
        status = "Cancelled";
    }

    void displayReservation() const {
        cout << left << setw(12) << reservationID
             << setw(14) << passengerID
             << setw(20) << passengerName
             << setw(10) << flightNumber
             << setw(8)  << seatNumber
             << setw(10) << seatClass
             << setw(12) << status
             << "PKR " << fixed << setprecision(2) << farePaid << "\n";
    }

    string toFileString() const {
        return reservationID + "," + passengerID + "," + passengerName + "," +
               flightNumber + "," + seatNumber + "," + seatClass + "," +
               to_string(farePaid) + "," + status;
    }
};

class ReservationManager {
private:
    vector<Reservation> reservations;
    string dataFilePath;

public:
    ReservationManager(string filePath = "data/reservations.txt") : dataFilePath(filePath) {
        loadReservationsFromFile();
    }

    string createReservation(const string& pID, const string& pName,
                             const string& fNum, const string& seatNo,
                             const string& seatClass, double fare) {
        string resID = "RES-" + to_string(1001 + reservations.size());
        reservations.emplace_back(resID, pID, pName, fNum, seatNo, seatClass, fare, "Confirmed");
        saveReservationsToFile();
        return resID;
    }

    string cancelReservation(const string& resID) {
        for (auto& r : reservations) {
            if (r.getReservationID() == resID && r.getStatus() == "Confirmed") {
                r.cancel();
                saveReservationsToFile();
                return r.getFlightNumber();
            }
        }
        return "";
    }

    void displayAllReservations() const {
        cout << "\n====================================================================================================\n";
        cout << left << setw(12) << "Res ID"
             << setw(14) << "Passenger ID"
             << setw(20) << "Name"
             << setw(10) << "Flight"
             << setw(8)  << "Seat"
             << setw(10) << "Class"
             << setw(12) << "Status"
             << "Fare Paid\n";
        cout << "----------------------------------------------------------------------------------------------------\n";
        for (const auto& r : reservations) {
            r.displayReservation();
        }
        cout << "====================================================================================================\n";
    }

    void printTicketByID(const string& resID, FleetScheduler& fleet) const {
        for (const auto& r : reservations) {
            if (r.getReservationID() == resID) {
                Flight* f = fleet.findFlight(r.getFlightNumber());
                string orig = f ? f->getOrigin() : "N/A";
                string dest = f ? f->getDestination() : "N/A";
                string dep  = f ? f->getDepartureTime() : "N/A";

                Ticketing::generateBoardingPass(
                    r.getReservationID(), r.getPassengerName(), r.getFlightNumber(),
                    orig, dest, dep, r.getSeatNumber(), r.getSeatClass(), r.getFarePaid()
                );
                return;
            }
        }
        cout << "Reservation ID not found!\n";
    }

    void saveReservationsToFile() const {
        ofstream outFile(dataFilePath);
        if (!outFile.is_open()) return;
        for (const auto& r : reservations) {
            outFile << r.toFileString() << "\n";
        }
        outFile.close();
    }

    void loadReservationsFromFile() {
        ifstream inFile(dataFilePath);
        if (!inFile.is_open()) return;

        reservations.clear();
        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;
            vector<string> fields;
            size_t start = 0, end;
            while ((end = line.find(',', start)) != string::npos) {
                fields.push_back(line.substr(start, end - start));
                start = end + 1;
            }
            fields.push_back(line.substr(start));

            if (fields.size() == 8) {
                reservations.emplace_back(
                    fields[0], fields[1], fields[2], fields[3],
                    fields[4], fields[5], stod(fields[6]), fields[7]
                );
            }
        }
        inFile.close();
    }
};

#endif // RESERVATION_H