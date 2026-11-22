#ifndef LOYALTY_H
#define LOYALTY_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class LoyaltyMember {
private:
    string passengerID;
    string passengerName;
    int points;
    string tierLevel; // Silver, Gold, Platinum

    void updateTier() {
        if (points >= 5000) {
            tierLevel = "Platinum";
        } else if (points >= 2000) {
            tierLevel = "Gold";
        } else {
            tierLevel = "Silver";
        }
    }

public:
    LoyaltyMember() : points(0), tierLevel("Silver") {}

    LoyaltyMember(string id, string name, int pts = 0)
        : passengerID(id), passengerName(name), points(pts) {
        updateTier();
    }

    // Getters
    string getPassengerID() const { return passengerID; }
    string getPassengerName() const { return passengerName; }
    int getPoints() const { return points; }
    string getTierLevel() const { return tierLevel; }

    double getTierDiscountRate() const {
        if (tierLevel == "Platinum") return 0.15; // 15% discount
        if (tierLevel == "Gold") return 0.10;     // 10% discount
        return 0.05;                              // 5% discount for Silver
    }

    // State Modifier
    void addPointsFromFare(double farePaid) {
        int earned = static_cast<int>(farePaid / 100.0);
        if (earned > 0) {
            points += earned;
            updateTier();
        }
    }

    void displayMember() const {
        cout << left << setw(15) << passengerID
             << setw(22) << passengerName
             << setw(12) << points
             << setw(12) << tierLevel
             << (getTierDiscountRate() * 100) << "%\n";
    }

    string toFileString() const {
        return passengerID + "," + passengerName + "," + to_string(points);
    }
};

class LoyaltyManager {
private:
    vector<LoyaltyMember> members;
    string dataFilePath;

public:
    LoyaltyManager(string filePath = "data/loyalty.txt") : dataFilePath(filePath) {
        loadMembersFromFile();
    }

    LoyaltyMember* findMember(const string& pID) {
        for (auto& m : members) {
            if (m.getPassengerID() == pID) {
                return &m;
            }
        }
        return nullptr;
    }

    void registerOrUpdateMember(const string& pID, const string& pName, double farePaid) {
        LoyaltyMember* existing = findMember(pID);
        if (existing) {
            existing->addPointsFromFare(farePaid);
        } else {
            LoyaltyMember newMember(pID, pName, 0);
            newMember.addPointsFromFare(farePaid);
            members.push_back(newMember);
        }
        saveMembersToFile();
    }

    void displayAllMembers() const {
        cout << "\n=====================================================================\n";
        cout << left << setw(15) << "Passenger ID"
             << setw(22) << "Name"
             << setw(12) << "Points"
             << setw(12) << "Tier"
             << "Discount\n";
        cout << "---------------------------------------------------------------------\n";
        for (const auto& m : members) {
            m.displayMember();
        }
        cout << "=====================================================================\n";
    }

    void saveMembersToFile() const {
        ofstream outFile(dataFilePath);
        if (!outFile.is_open()) return;
        for (const auto& m : members) {
            outFile << m.toFileString() << "\n";
        }
        outFile.close();
    }

    void loadMembersFromFile() {
        ifstream inFile(dataFilePath);
        if (!inFile.is_open()) return;

        members.clear();
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

            if (fields.size() == 3) {
                members.emplace_back(fields[0], fields[1], stoi(fields[2]));
            }
        }
        inFile.close();
    }
};

#endif // LOYALTY_H