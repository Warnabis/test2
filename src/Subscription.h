#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Functions.h"
#include "Activation.h"



class Subscription : public Activation{
private:
    int id;
    float price;
    int days;
    std::string name;
    bool activated = false;

public:
    Subscription(int id = 0, float price = 0.0f, int days = 0, const std::string& name = "")
        : id(id), price(price), days(days), name(name) {}

    friend void wait();
    void input();
    friend void output(const Subscription& service);

    
    void setName(const std::string& name) { this->name = name; }
    void setPrice(float price) { this->price = price; }
    void setDays(int days) { this->days = days; }

    std::string getName() const { return name; }
    float getPrice() const { return price; }
    int getDays() const { return days; }

    void savetofile(std::ofstream& ofs) const;
    void loadfromfile(std::ifstream& ifs);


    void create(std::vector<Subscription>& services) const;
    void read(const std::vector<Subscription>& services) const;
    void update(std::vector<Subscription>& services) const;
    void deletes(std::vector<Subscription>& services) const;
    void workout(std::vector<Subscription>& services, Subscription*& selectedservice) const;
    void compareprices(const std::vector<Subscription>& services) const;

    friend bool operator==(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price == rhs.price;
    }

    friend bool operator>(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price > rhs.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Subscription& sub) {
        os << "\n" << "Айди: " << sub.id << "\n" << "Имя: " << sub.name
            << "\n" << "Цена: " << sub.price << "\n" << "Кол-во занятий: " << sub.days << "\n";
        return os;
    }

    void activate() override {
        if (!activated) { 
            activated = true;
            std::cout << "Подписка \"" << name << "\" активирована." << std::endl;
        }
        else {
            std::cout << "Подписка \"" << name << "\" уже активирована." << std::endl;
        }
    }

    void deactivate() override {
        if (activated) {
            activated = false;
            std::cout << "Подписка \"" << name << "\" деактивирована." << std::endl;
        }
        else {
            std::cout << "Подписка \"" << name << "\" уже деактивирована." << std::endl;
        }
    }

    bool isActivated() const override {
        return activated;
    }
};

#endif 