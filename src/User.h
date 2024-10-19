#ifndef USER_H
#define USER_H

#include "Person.h"
#include "Subscription.h"
#include "Place.h"
#include <vector>
#include <memory> // Для использования std::shared_ptr

class User : public Person {
private:
    std::vector<std::shared_ptr<Subscription>> subscriptions; // Изменено на shared_ptr
    std::vector<Place> places;

public:
    User(const std::string& login = "user", const std::string& password = "user")
        : Person(login, password) {}

    void showMenu(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions); // Изменено на shared_ptr
    void viewSubscriptions() const; // Удалён параметр, используйте член subscriptions
    void viewPlaces() const; // Удалён параметр, используйте член places

    void workout(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions, std::shared_ptr<Subscription>& selectedService) const; // Изменено на shared_ptr
    void comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const; // Изменено на shared_ptr

    // Новые методы для отображения деталей подписки
    void displaySubscriptionDetails(const Subscription& subscription) const;
};

#endif // USER_H
