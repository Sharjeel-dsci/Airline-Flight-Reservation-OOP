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

    // 1. Sharjeel Usman's Module: Seat & Reservation Management
    cout << "--- [Module 1: Seat & Reservation Management] ---" << endl;
    Seat seat1("12A", "Business");
    seat1.bookSeat();
    seat1.displaySeat();

    Reservation res1(101, "Ahmed Raza", "PK-304");
    res1.displayReservation();
    cout << endl;

    // 2. Muhammad Mahmood Waleed's Module: Flight Schedule & Pricing
    cout << "--- [Module 2: Flight Schedule & Pricing Policy] ---" << endl;
    FlightSchedule flight1("PK-304", "Lahore", "Islamabad", "04:30 PM");
    flight1.displaySchedule();

    PricingPolicy price1("Business", 25000.0);
    price1.displayFare();
    cout << endl;

    // 3. Ameer Haroon's Module: Frequent Flyer Loyalty Program
    cout << "--- [Module 3: Loyalty & Frequent Flyer Program] ---" << endl;
    LoyaltyAccount loyalty1("FF-786", "Ahmed Raza", 1200);
    loyalty1.addPoints(300);
    loyalty1.displayLoyalty();
    cout << endl;

    // 4. Azeemfatima's Module: Ticketing & Boarding Pass
    cout << "--- [Module 4: Ticketing & Boarding Pass] ---" << endl;
    Ticket ticket1("TKT-9001", "Ahmed Raza", "G-04");
    ticket1.displayBoardingPass();
    cout << endl;

    cout << "========================================================" << endl;
    cout << "     All Milestone 1 Module Objects Executed Successfully " << endl;
    cout << "========================================================" << endl;

    return 0;
}