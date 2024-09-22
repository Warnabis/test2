#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#include <iostream>
#include <string>
#include <vector>

class Subscription {
public:
    int id;
    std::string name;
    int price;
    int days;

    void input();
    void output() const;
    void create(std::vector<Subscription>& services) const;
    void read(const std::vector<Subscription>& services) const;
    void update(std::vector<Subscription>& services) const;
    void deletes(std::vector<Subscription>& services) const;
    void workout(std::vector<Subscription>& services, Subscription*& selectedservice) const;

private:
    void wait() const;
};

#endif
