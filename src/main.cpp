#include <iostream>
#include "Seat.h"
#include "Reservation.h"
#include "FlightSchedule.h"
#include "PricingPolicy.h"
#include "Loyalty.h"
#include "Ticketing.h"

using namespace std;

int main() {
    cout << "========================================================" << endl;
    cout << "  Airline Flight Reservation System - Milestone 1 Demo  " << endl;
    cout << "========================================================" << endl << endl;

    // Module 2: Seat & Reservation Management (Sharjeel Usman)
    cout << "--- [Module 2: Seat & Reservation Management] ---" << endl;
    Seat seat1("12A", "Business");
    seat1.bookSeat();
    seat1.displaySeat();

    Reservation res1(101, "Ahmed Raza", "PK-304");
    res1.displayReservation();
    cout << endl;

    // Module 3: Flight Schedule & Pricing Policy (Muhammad Mahmood Waleed)
    cout << "--- [Module 3: Flight Schedule & Pricing Policy] ---" << endl;
    FlightSchedule flight1("PK-304", "Lahore", "Islamabad", "04:30 PM");
    flight1.displaySchedule();

    PricingPolicy price1("Business", 25000.0);
    price1.displayFare();
    cout << endl;

    // Module 4: Loyalty & Frequent Flyer Program (Ameer Haroon)
    cout << "--- [Module 4: Loyalty & Frequent Flyer Program] ---" << endl;
    LoyaltyAccount loyalty1("FF-786", "Ahmed Raza", 1200);
    loyalty1.addPoints(300);
    loyalty1.displayLoyalty();
    cout << endl;

    // Module 5: Ticketing & Boarding Pass (Azeemfatima)
    cout << "--- [Module 5: Ticketing & Boarding Pass] ---" << endl;
    Ticket ticket1("TKT-9001", "Ahmed Raza", "G-04");
    ticket1.displayBoardingPass();
    cout << endl;

    cout << "========================================================" << endl;
    cout << "     All Milestone 1 Module Objects Executed Successfully " << endl;
    cout << "========================================================" << endl;

    return 0;
}
