#ifndef TICKETING_H
#define TICKETING_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Ticket {
private:
    string ticketID;
    string reservationID;
    string passengerName;
    string flightNumber;
    string seatNumber;
    string seatClass;
    double finalFare;
    string status; // "Issued", "Checked-In", "Cancelled"

public:
    // Default & Parameterized Constructors
    Ticket() : finalFare(0.0), status("Pending") {}

    Ticket(string tID, string resID, string pName, string fNum,
           string sNum, string sClass, double fare, string stat = "Issued")
        : ticketID(tID), reservationID(resID), passengerName(pName),
          flightNumber(fNum), seatNumber(sNum), seatClass(sClass),
          finalFare(fare), status(stat) {}

    // Getters
    string getTicketID() const { return ticketID; }
    string getReservationID() const { return reservationID; }
    string getPassengerName() const { return passengerName; }
    string getFlightNumber() const { return flightNumber; }
    string getSeatNumber() const { return seatNumber; }
    string getSeatClass() const { return seatClass; }
    double getFinalFare() const { return finalFare; }
    string getStatus() const { return status; }

    // Setters / State Modifiers
    void checkIn() {
        if (status == "Issued") {
            status = "Checked-In";
        }
    }

    void cancelTicket() {
        status = "Cancelled";
    }

    // Formatted Boarding Pass / E-Ticket Display
    void displayTicket() const {
        cout << "\n=============================================\n";
        cout << "           AIRLINE E-TICKET / PASS           \n";
        cout << "=============================================\n";
        cout << " Ticket ID      : " << ticketID << "\n";
        cout << " Reservation ID : " << reservationID << "\n";
        cout << " Passenger      : " << passengerName << "\n";
        cout << " Flight No.     : " << flightNumber << "\n";
        cout << " Seat & Class   : " << seatNumber << " (" << seatClass << ")\n";
        cout << " Total Fare     : PKR " << fixed << setprecision(2) << finalFare << "\n";
        cout << " Status         : " << status << "\n";
        cout << "=============================================\n";
    }

    // Serialize to CSV format for data/tickets.txt
    string toFileString() const {
        return ticketID + "," + reservationID + "," + passengerName + "," +
               flightNumber + "," + seatNumber + "," + seatClass + "," +
               to_string(finalFare) + "," + status;
    }
};

class TicketingManager {
private:
    vector<Ticket> tickets;
    string dataFilePath;

public:
    TicketingManager(string filePath = "data/tickets.txt") : dataFilePath(filePath) {
        loadTicketsFromFile();
    }

    // Issue a new ticket and save to file
    Ticket issueTicket(string resID, string pName, string fNum,
                       string sNum, string sClass, double fare) {
        string newTicketID = "TKT-" + to_string(1001 + tickets.size());
        Ticket newTicket(newTicketID, resID, pName, fNum, sNum, sClass, fare, "Issued");
        tickets.push_back(newTicket);
        saveTicketsToFile();
        return newTicket;
    }

    // Search ticket by ID
    Ticket* findTicket(const string& tID) {
        for (auto& t : tickets) {
            if (t.getTicketID() == tID) {
                return &t;
            }
        }
        return nullptr;
    }

    // Cancel a ticket by ID
    bool cancelTicketByID(const string& tID) {
        Ticket* t = findTicket(tID);
        if (t != nullptr && t->getStatus() != "Cancelled") {
            t->cancelTicket();
            saveTicketsToFile();
            return true;
        }
        return false;
    }

    // Display all issued tickets
    void displayAllTickets() const {
        if (tickets.empty()) {
            cout << "\nNo tickets issued yet.\n";
            return;
        }
        for (const auto& t : tickets) {
            t.displayTicket();
        }
    }

    // File Handling: Save all tickets to data/tickets.txt
    void saveTicketsToFile() const {
        ofstream outFile(dataFilePath);
        if (!outFile.is_open()) return;

        for (const auto& t : tickets) {
            outFile << t.toFileString() << "\n";
        }
        outFile.close();
    }

    // File Handling: Load existing tickets on startup
    void loadTicketsFromFile() {
        ifstream inFile(dataFilePath);
        if (!inFile.is_open()) return;

        tickets.clear();
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
                tickets.emplace_back(
                    fields[0], fields[1], fields[2], fields[3],
                    fields[4], fields[5], stod(fields[6]), fields[7]
                );
            }
        }
        inFile.close();
    }
};

#endif // TICKETING_H