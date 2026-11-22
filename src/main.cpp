#include <iostream>
#include <string>
#include <limits>

// Including All Project Modules
#include "../include/FlightSchedule.h"
#include "../include/PricingPolicy.h"
#include "../include/Seat.h"
#include "../include/Reservation.h"
#include "../include/Loyalty.h"
#include "../include/Ticketing.h"

using namespace std;

class AirlineSystemController {
private:
    FleetScheduler fleet;
    PricingPolicy pricing;
    ReservationManager reservations;
    LoyaltyManager loyalty;

    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    void showMainMenu() {
        int choice = 0;
        do {
            cout << "\n==========================================================\n";
            cout << "      AIRLINE FLIGHT RESERVATION & FLEET SYSTEM (MOD 1)   \n";
            cout << "==========================================================\n";
            cout << "1. View All Scheduled Flights (Fleet Module)\n";
            cout << "2. Add New Flight to Schedule (Admin)\n";
            cout << "3. Book a Flight Ticket (Reservation + Pricing + Loyalty)\n";
            cout << "4. View All Reservations\n";
            cout << "5. Cancel a Reservation\n";
            cout << "6. Check Frequent Flyer Loyalty Status\n";
            cout << "7. Generate Boarding Pass / Ticket\n";
            cout << "0. Exit System\n";
            cout << "----------------------------------------------------------\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                clearInputBuffer();
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            clearInputBuffer();

            switch (choice) {
                case 1:
                    fleet.displayAllFlights();
                    break;
                case 2:
                    handleAddFlight();
                    break;
                case 3:
                    handleBookTicket();
                    break;
                case 4:
                    reservations.displayAllReservations();
                    break;
                case 5:
                    handleCancelReservation();
                    break;
                case 6:
                    loyalty.displayAllMembers();
                    break;
                case 7:
                    handlePrintBoardingPass();
                    break;
                case 0:
                    cout << "Saving all records and exiting system. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid option! Try again.\n";
            }
        } while (choice != 0);
    }

    void handleAddFlight() {
        string fNum, model, orig, dest, depTime;
        int seats;
        double fare;

        cout << "\n--- Add New Flight ---\n";
        cout << "Flight Number (e.g., PK-502): "; getline(cin, fNum);
        cout << "Aircraft Model (e.g., Boeing 777): "; getline(cin, model);
        cout << "Origin City: "; getline(cin, orig);
        cout << "Destination City: "; getline(cin, dest);
        cout << "Departure Time (e.g., 06:00 PM): "; getline(cin, depTime);
        cout << "Total Seats: "; cin >> seats;
        cout << "Base Fare (PKR): "; cin >> fare;
        clearInputBuffer();

        Flight newFlight(fNum, model, orig, dest, depTime, seats, seats, fare);
        fleet.addFlight(newFlight);
        cout << "Flight " << fNum << " added successfully!\n";
    }

    void handleBookTicket() {
        string pID, pName, fNum, seatClass, seatNo;
        cout << "\n--- Book a Flight Ticket ---\n";
        fleet.displayAllFlights();

        cout << "Enter Flight Number to book: "; getline(cin, fNum);
        Flight* selectedFlight = fleet.findFlight(fNum);
        if (!selectedFlight) {
            cout << "Flight not found!\n";
            return;
        }
        if (selectedFlight->getAvailableSeats() <= 0) {
            cout << "Sorry, no seats available on this flight!\n";
            return;
        }

        cout << "Passenger CNIC / ID: "; getline(cin, pID);
        cout << "Passenger Full Name: "; getline(cin, pName);
        cout << "Seat Class (Economy / Business): "; getline(cin, seatClass);
        cout << "Preferred Seat Number (e.g., 12A): "; getline(cin, seatNo);

        // 1. Calculate Dynamic Fare (Module 3)
        double finalFare = pricing.calculateFinalFare(
            selectedFlight->getBaseFare(),
            selectedFlight->getOccupancyRate(),
            seatClass
        );

        // 2. Apply Loyalty Discount if existing member (Module 4)
        LoyaltyMember* member = loyalty.findMember(pID);
        if (member) {
            double discount = finalFare * member->getTierDiscountRate();
            finalFare -= discount;
            cout << "Loyalty Tier (" << member->getTierLevel() << ") Discount Applied: -PKR " << discount << "\n";
        }

        // 3. Allocate Seat & Create Reservation (Module 2 & 3)
        if (selectedFlight->allocateSeat()) {
            fleet.saveFlightsToFile();
            string resID = reservations.createReservation(pID, pName, fNum, seatNo, seatClass, finalFare);
            loyalty.registerOrUpdateMember(pID, pName, finalFare);

            cout << "\nBooking Confirmed! Reservation ID: " << resID << "\n";
            cout << "Final Payable Fare: PKR " << finalFare << "\n";

            // 4. Generate Boarding Pass (Module 5)
            Ticketing::generateBoardingPass(resID, pName, fNum, selectedFlight->getOrigin(),
                                            selectedFlight->getDestination(), selectedFlight->getDepartureTime(),
                                            seatNo, seatClass, finalFare);
        }
    }

    void handleCancelReservation() {
        string resID;
        cout << "\nEnter Reservation ID to cancel: ";
        getline(cin, resID);

        string flightNum = reservations.cancelReservation(resID);
        if (!flightNum.empty()) {
            Flight* f = fleet.findFlight(flightNum);
            if (f) {
                f->releaseSeat();
                fleet.saveFlightsToFile();
            }
            cout << "Reservation " << resID << " cancelled and seat released!\n";
        } else {
            cout << "Reservation ID not found!\n";
        }
    }

    void handlePrintBoardingPass() {
        string resID;
        cout << "\nEnter Reservation ID for Boarding Pass: ";
        getline(cin, resID);
        reservations.printTicketByID(resID, fleet);
    }
};

int main() {
    AirlineSystemController app;
    app.showMainMenu();
    return 0;
}