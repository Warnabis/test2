#ifndef USER_H
#define USER_H

#include "Person.h"
#include "Subscription.h"
#include "Place.h"
#include <vector>
#include <memory> // ��� ������������� std::shared_ptr

class User : public Person {
private:
    std::vector<std::shared_ptr<Subscription>> subscriptions; // �������� �� shared_ptr
    std::vector<Place> places;

public:
    User(const std::string& login = "user", const std::string& password = "user")
        : Person(login, password) {}

    void showMenu(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions); // �������� �� shared_ptr
    void viewSubscriptions() const; // ����� ��������, ����������� ���� subscriptions
    void viewPlaces() const; // ����� ��������, ����������� ���� places

    void workout(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions, std::shared_ptr<Subscription>& selectedService) const; // �������� �� shared_ptr
    void comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const; // �������� �� shared_ptr

    // ����� ������ ��� ����������� ������� ��������
    void displaySubscriptionDetails(const Subscription& subscription) const;
};

#endif // USER_H
