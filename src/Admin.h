
#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include "Place.h"
#include "Subscription.h"
#include <vector>
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include "memory"

class Admin : public Person {
public:
    Admin(const std::string& login = "admin", const std::string& password = "admin")
        : Person(login, password) {}

    void showMenu(std::vector<Place>& places, std::vector<std::shared_ptr<Subscription>>& subscriptions);

    void managePlaces(std::vector<Place>& places, std::vector<std::shared_ptr<Subscription>>& subscriptions);

    void manageSubscriptions(std::vector<std::shared_ptr<Subscription>>& subscriptions);

    void loadAllPlacesFromFile(std::vector<Place>& places);
    void saveAllPlacesToFile(const std::vector<Place>& places);
    void loadAllSubscriptionsFromFile(std::vector<std::shared_ptr<Subscription>>& subscriptions);
    void saveAllSubscriptionsToFile(const std::vector<std::shared_ptr<Subscription>>& subscriptions);

    void createSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions);
    void readSubscriptions(const std::vector<std::shared_ptr<Subscription>>& subscriptions) const;
    void updateSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions);
    void deleteSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions);
};

#endif 
