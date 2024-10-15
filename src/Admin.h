#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include "Place.h"
#include "Subscription.h"
#include <vector>

class Admin : public Person {
public:
    Admin(const std::string& login, const std::string& password)
        : Person(login, password) {}

    void showMenu(std::vector<Place>& places, std::vector<Subscription>& subscriptions);

    void managePlaces(std::vector<Place>& places);

    void manageSubscriptions(std::vector<Subscription>& subscriptions);
};

#endif