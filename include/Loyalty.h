#ifndef LOYALTY_H
#define LOYALTY_H
#include <iostream>
#include <string>
using namespace std;

class LoyaltyAccount {
private:
    string memberID;
    string memberName;
    int points;
    string tier;

    void updateTier() {
        if (points >= 5000) tier = "Platinum";
        else if (points >= 2000) tier = "Gold";
        else tier = "Silver";
    }

public:
    LoyaltyAccount() : memberID("FF-000"), memberName("Guest"), points(0), tier("Silver") {}
    LoyaltyAccount(string id, string name, int pts) : memberID(id), memberName(name), points(0), tier("Silver") {
        addPoints(pts);
    }
    // Getters
    string getMemberID() const { return memberID; }
    string getMemberName() const { return memberName; }
    int getPoints() const { return points; }
    string getTier() const { return tier; }

    // Setters & Validated Operations
    void setMemberName(string name) { if (!name.empty()) memberName = name; }
    void addPoints(int pts) {
        if (pts > 0) {
            points += pts;
            updateTier();
        }
    }
    bool redeemPoints(int pts) {
        if (pts > 0 && points >= pts) {
            points -= pts;
            updateTier();
            return true;
        }
        return false;
    }

    void displayLoyalty() const {
        cout << "Loyalty ID: " << memberID << " | Member: " << memberName
             << " | Points: " << points << " | Tier: " << tier << endl;
    }
};

class RewardItem {
private:
    string rewardID;
    string rewardTitle;
    int requiredPoints;

public:
    RewardItem() : rewardID("RWD-00"), rewardTitle("None"), requiredPoints(500) {}
    RewardItem(string id, string title, int reqPts) : rewardID(id), rewardTitle(title) {
        setRequiredPoints(reqPts);
    }

    // Getters
    string getRewardID() const { return rewardID; }
    string getRewardTitle() const { return rewardTitle; }
    int getRequiredPoints() const { return requiredPoints; }

    // Setters with Validation
    void setRequiredPoints(int reqPts) { requiredPoints = (reqPts > 0) ? reqPts : 500; }

    void displayReward() const {
        cout << "Reward [" << rewardID << "]: " << rewardTitle
             << " | Required Points: " << requiredPoints << endl;
    }
};

class LoyaltyTransaction {
private:
    string transactionID;
    string memberID;
    string type;
    int pointsChanged;

public:
    LoyaltyTransaction() : transactionID("TXN-000"), memberID("FF-000"), type("Earn"), pointsChanged(0) {}
    LoyaltyTransaction(string txnId, string memId, string txnType, int pts)
        : transactionID(txnId), memberID(memId), type(txnType) {
        pointsChanged = (pts >= 0) ? pts : 0;
    }

    // Getters
    string getTransactionID() const { return transactionID; }
    string getMemberID() const { return memberID; }
    string getType() const { return type; }
    int getPointsChanged() const { return pointsChanged; }

    void displayTransaction() const {
        cout << "Transaction [" << transactionID << "] | Member: " << memberID
             << " | Type: " << type << " | Points: " << pointsChanged << endl;
    }
};
#endif
