#ifndef FLIGHT_SCHEDULE_H
#define FLIGHT_SCHEDULE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Flight {
private:
    string flightNumber;
    string aircraftModel;
    string origin;
    string destination;
    string departureTime;
    int totalSeats;
    int availableSeats;
    double baseFare;

public:
    Flight() : totalSeats(0), availableSeats(0), baseFare(0.0) {}

    Flight(string fNum, string model, string orig, string dest,
           string depTime, int totSeats, int availSeats, double fare) {
        setFlightNumber(fNum);
        setAircraftModel(model);
        setRoute(orig, dest);
        setDepartureTime(depTime);
        setSeats(totSeats, availSeats);
        setBaseFare(fare);
    }

    void setFlightNumber(const string& fNum) {
        if (!fNum.empty()) flightNumber = fNum;
    }

    void setAircraftModel(const string& model) {
        if (!model.empty()) aircraftModel = model;
    }

    void setRoute(const string& orig, const string& dest) {
        if (!orig.empty() && !dest.empty()) {
            origin = orig;
            destination = dest;
        }
    }

    void setDepartureTime(const string& depTime) {
        if (!depTime.empty()) departureTime = depTime;
    }

    void setSeats(int totSeats, int availSeats) {
        if (totSeats > 0) {
            totalSeats = totSeats;
            if (availSeats >= 0 && availSeats <= totSeats) {
                availableSeats = availSeats;
            } else {
                availableSeats = totSeats;
            }
        }
    }

    void setBaseFare(double fare) {
        if (fare >= 0.0) {
            baseFare = fare;
        }
    }

    string getFlightNumber() const { return flightNumber; }
    string getAircraftModel() const { return aircraftModel; }
    string getOrigin() const { return origin; }
    string getDestination() const { return destination; }
    string getDepartureTime() const { return departureTime; }
    int getTotalSeats() const { return totalSeats; }
    int getAvailableSeats() const { return availableSeats; }
    double getBaseFare() const { return baseFare; }

    bool allocateSeat() {
        if (availableSeats > 0) {
            availableSeats--;
            return true;
        }
        return false;
    }

    bool releaseSeat() {
        if (availableSeats < totalSeats) {
            availableSeats++;
            return true;
        }
        return false;
    }

    double getOccupancyRate() const {
        if (totalSeats == 0) return 0.0;
        return static_cast<double>(totalSeats - availableSeats) / totalSeats;
    }

    void displayFlight() const {
        cout << left << setw(10) << flightNumber
             << setw(16) << aircraftModel
             << setw(14) << origin
             << setw(14) << destination
             << setw(12) << departureTime
             << setw(10) << (to_string(availableSeats) + "/" + to_string(totalSeats))
             << "PKR " << fixed << setprecision(2) << baseFare << "\n";
    }

    string toFileString() const {
        return flightNumber + "," + aircraftModel + "," + origin + "," +
               destination + "," + departureTime + "," +
               to_string(totalSeats) + "," + to_string(availableSeats) + "," +
               to_string(baseFare);
    }
};

class FleetScheduler {
private:
    vector<Flight> flights;
    string dataFilePath;

public:
    FleetScheduler(string filePath = "data/flights.txt") : dataFilePath(filePath) {
        loadFlightsFromFile();
        if (flights.empty()) {
            seedDefaultFleet();
        }
    }

    void seedDefaultFleet() {
        flights.emplace_back("PK-301", "Boeing 777", "Lahore", "Karachi", "09:00 AM", 120, 120, 18500.0);
        flights.emplace_back("PK-405", "Airbus A320", "Islamabad", "Dubai", "02:30 PM", 90, 90, 52000.0);
        flights.emplace_back("PK-711", "Boeing 787", "Lahore", "London", "11:45 PM", 150, 150, 145000.0);
        saveFlightsToFile();
    }

    void addFlight(const Flight& newFlight) {
        flights.push_back(newFlight);
        saveFlightsToFile();
    }

    Flight* findFlight(const string& fNum) {
        for (auto& f : flights) {
            if (f.getFlightNumber() == fNum) {
                return &f;
            }
        }
        return nullptr;
    }

    int getTotalFlightsCount() const {
        return static_cast<int>(flights.size());
    }

    void displayAllFlights() const {
        cout << "\n=========================================================================================\n";
        cout << left << setw(10) << "Flight"
             << setw(16) << "Aircraft"
             << setw(14) << "Origin"
             << setw(14) << "Destination"
             << setw(12) << "Departure"
             << setw(10) << "Seats"
             << "Base Fare\n";
        cout << "-----------------------------------------------------------------------------------------\n";
        for (const auto& f : flights) {
            f.displayFlight();
        }
        cout << "=========================================================================================\n";
    }

    void saveFlightsToFile() const {
        ofstream outFile(dataFilePath);
        if (!outFile.is_open()) return;
        for (const auto& f : flights) {
            outFile << f.toFileString() << "\n";
        }
        outFile.close();
    }

    void loadFlightsFromFile() {
        ifstream inFile(dataFilePath);
        if (!inFile.is_open()) return;

        flights.clear();
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
                flights.emplace_back(
                    fields[0], fields[1], fields[2], fields[3],
                    fields[4], stoi(fields[5]), stoi(fields[6]), stod(fields[7])
                );
            }
        }
        inFile.close();
    }
};

#endif 