#ifndef USER_H
#define USER_H

#include "Person.h"
#include "Subscription.h"
#include "Place.h"
#include <vector>

class User : public Person {
private:
    std::vector<Subscription> subscriptions;
    std::vector<Place> places;

public:
    User(const std::string& login, const std::string& password)
        : Person(login, password) {}

    void showMenu() override;  
    void viewSubscriptions() const;
    void viewPlaces() const;
};

#endif