#include <iostream>
#include "Seat.h"
#include "Reservation.h"
#include "FlightSchedule.h"
#include "PricingPolicy.h"
#include "Loyalty.h"
#include "Ticketing.h"

using namespace std;

int main() {
    cout << "======================================================================" << endl;
    cout << "   Airline Flight Reservation System - Complete OOP Architecture      " << endl;
    cout << "======================================================================" << endl << endl;

    // --------------------------------------------------------------------------
    // Module 2: Passenger, Seat & Reservation Management (Sharjeel Usman)
    // --------------------------------------------------------------------------
    cout << "--- [Module 2: Passenger, Seat & Reservation Management] ---" << endl;
    Passenger p1("P-101", "Ahmed Raza", "35202-1234567-1", 28);
    p1.displayPassenger();

    Seat seat1("12A", "Business");
    seat1.bookSeat();
    seat1.displaySeat();

    Reservation res1(5001, p1.getFullName(), "PK-304", seat1.getSeatNumber());
    res1.displayReservation();
    cout << endl;

    // --------------------------------------------------------------------------
    // Module 3: Fleet, Flight Schedule & Pricing Policy (Muhammad Mahmood Waleed)
    // --------------------------------------------------------------------------
    cout << "--- [Module 3: Fleet, Flight Schedule & Pricing Policy] ---" << endl;
    Aircraft plane1("AP-BMG", "Boeing 777-300ER", 393);
    plane1.displayAircraft();

    FlightSchedule flight1("PK-304", "Lahore", "Islamabad", "04:30 PM", 45);
    flight1.allocateSeat();
    flight1.displaySchedule();

    PricingPolicy price1("Business", 25000.0, 16.0);
    price1.displayFare();
    cout << endl;

    // --------------------------------------------------------------------------
    // Module 4: Loyalty & Frequent Flyer Program (Ameer Haroon)
    // --------------------------------------------------------------------------
    cout << "--- [Module 4: Loyalty & Frequent Flyer Program] ---" << endl;
    LoyaltyAccount loyalty1("FF-786", p1.getFullName(), 1800);
    loyalty1.addPoints(400); // Auto upgrades to Gold tier
    loyalty1.displayLoyalty();

    RewardItem reward1("RWD-01", "Priority Lounge Access", 500);
    reward1.displayReward();

    if (loyalty1.redeemPoints(reward1.getRequiredPoints())) {
        LoyaltyTransaction txn1("TXN-901", loyalty1.getMemberID(), "Redeem", reward1.getRequiredPoints());
        txn1.displayTransaction();
    }
    cout << endl;

    // --------------------------------------------------------------------------
    // Module 5: Ticketing, Boarding Pass & Baggage (Azeemfatima)
    // --------------------------------------------------------------------------
    cout << "--- [Module 5: Ticketing, Boarding Pass & Baggage] ---" << endl;
    Ticket ticket1("TKT-9001", "PNR78X", p1.getFullName(), price1.calculateTotalFare());
    ticket1.displayTicket();

    BoardingPass bp1("BP-304A", p1.getFullName(), "G-04", "03:45 PM");
    bp1.markBoarded();
    bp1.displayBoardingPass();

    BaggageTag bag1("BAG-442", p1.getFullName(), 24.5); // 4.5kg extra -> PKR 2250 fee
    bag1.displayBaggageTag();
    cout << endl;

    cout << "======================================================================" << endl;
    cout << "     All 12 Module Classes & Objects Executed Successfully!           " << endl;
    cout << "======================================================================" << endl;

    return 0;
}
