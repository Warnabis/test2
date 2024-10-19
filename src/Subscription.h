#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class Activation {
public:
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual bool isActivated() const = 0;
    virtual ~Activation() = default;
};

class Subscription : public Activation {
protected:
    int id;
    std::string name;
    double price;
    int days;
    bool activated = false;

public:
    Subscription(int id = 0, const std::string& name = "", float price = 0.0f, int days = 0)
        : id(id), name(name), price(price), days(days) {}

    virtual ~Subscription() = default;

    virtual void display() const = 0;       // ����� ����������� �������
    virtual void decrementDays() = 0;      // ����� ����������� �������
    virtual bool isExpired() const = 0;     // ����� ����������� �������

    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getDays() const { return days; }
    int getId() const { return id; }

    void setId(int newId) {
        id = newId;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    void setDays(int newDays) {
        days = newDays;
    }

    virtual void saveToFile(std::ofstream& ofs) const; // ���������� �������� � ����
    virtual void loadFromFile(std::ifstream& ifs);     // �������� �������� �� �����

    void comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const;

    // ���������� ����������
    friend bool operator==(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price == rhs.price;
    }

    friend bool operator>(const Subscription& lhs, const Subscription& rhs) {
        return lhs.price > rhs.price;
    }

    friend std::ostream& operator<<(std::ostream& os, const Subscription& subscription) {
        os << subscription.id << ' ' << subscription.name << ' ' << subscription.price << ' ' << subscription.days;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Subscription& subscription) {
        is >> subscription.id >> subscription.name >> subscription.price >> subscription.days;
        return is;
    }

    // ������ ��������� ��������
    void activate() override {
        if (!activated) {
            activated = true;
            std::cout << "�������� \"" << name << "\" ������������." << std::endl;
        }
        else {
            std::cout << "�������� \"" << name << "\" ��� ������������." << std::endl;
        }
    }

    void deactivate() override {
        if (activated) {
            activated = false;
            std::cout << "�������� \"" << name << "\" ��������������." << std::endl;
        }
        else {
            std::cout << "�������� \"" << name << "\" ��� ��������������." << std::endl;
        }
    }

    bool isActivated() const override {
        return activated;
    }
};

#endif
