#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include "Subscription.h"
#include "Place.h"
#include <vector>

class Admin : public Person {
private:
    std::vector<Subscription> subscriptions;
    std::vector<Place> places;

public:
    Admin(const std::string& login, const std::string& password);

    void showMenu() override;
    void manageSubscriptions();
    void managePlaces();

    // CRUD операции для подписок и залов
    void createSubscription();
    void readSubscriptions();
    void updateSubscription();
    void deleteSubscription();

    void createPlace();
    void readPlaces();
    void updatePlace();
    void deletePlace();
};

#endif