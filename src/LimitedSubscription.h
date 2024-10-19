#ifndef LIMITEDSUBSCRIPTION_H
#define LIMITEDSUBSCRIPTION_H

#include "Subscription.h"

class LimitedSubscription : public Subscription {
private:
    int sessions; // Количество занятий

public:
    LimitedSubscription(int id = 0, const std::string& name = "", float price = 0.0f, int days = 0, int sessions = 0)
        : Subscription(id, name, price, days), sessions(sessions) {}

    void display() const override {
        std::cout << "Ограниченная подписка: " << name << ", цена: " << price << ", дней: " << days << ", занятий: " << sessions << std::endl;
    }

    void decrementDays() override {
        if (days > 0) {
            --days;
        }
    }

    bool isExpired() const override {
        return days <= 0;
    }

    void saveToFile(std::ofstream& ofs) const override {
        Subscription::saveToFile(ofs);
        ofs << sessions << '\n';
    }

    void loadFromFile(std::ifstream& ifs) override {
        Subscription::loadFromFile(ifs);
        ifs >> sessions;
    }
};

#endif