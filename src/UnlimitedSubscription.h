#ifndef UNLIMITEDSUBSCRIPTION_H
#define UNLIMITEDSUBSCRIPTION_H

#include "Subscription.h"

class UnlimitedSubscription : public Subscription {
public:
    UnlimitedSubscription(int id = 0, const std::string& name = "", float price = 0.0f, int days = 0)
        : Subscription(id, name, price, days) {}

    void display() const override {
        std::cout << "Безлимитная подписка: " << name << ", цена: " << price << ", дней: " << days << std::endl;
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
    }

    void loadFromFile(std::ifstream& ifs) override {
        Subscription::loadFromFile(ifs);
    }
};

#endif
