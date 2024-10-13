#include "Admin.h"
#include <iostream>

Admin::Admin(const std::string& login, const std::string& password)
    : Person(login, password) {}

void Admin::manageSubscriptions() {
    int choice;
    do {
        std::cout << "\n���������� ����������:\n";
        std::cout << "1. ������� ��������\n";
        std::cout << "2. ��������� ��������\n";
        std::cout << "3. �������� ��������\n";
        std::cout << "4. ������� ��������\n";
        std::cout << "5. ����� � ���� ��������������\n";
        std::cout << "�������� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            createSubscription();
            break;
        case 2:
            readSubscriptions();
            break;
        case 3:
            updateSubscription();
            break;
        case 4:
            deleteSubscription();
            break;
        case 5:
            std::cout << "������� � ���� ��������������.\n";
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 5);
}

void Admin::managePlaces() {
    int choice;
    do {
        std::cout << "\n���������� ������:\n";
        std::cout << "1. ������� ���\n";
        std::cout << "2. ��������� ����\n";
        std::cout << "3. �������� ���\n";
        std::cout << "4. ������� ���\n";
        std::cout << "5. ����� � ���� ��������������\n";
        std::cout << "�������� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            createPlace();
            break;
        case 2:
            readPlaces();
            break;
        case 3:
            updatePlace();
            break;
        case 4:
            deletePlace();
            break;
        case 5:
            std::cout << "������� � ���� ��������������.\n";
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 5);
}

void Admin::createSubscription() {
    Subscription sub;
    std::cout << "������� �������� ��������: ";
    std::string name;
    std::cin >> name;
    sub.setName(name);

    std::cout << "������� ���� ��������: ";
    float price;
    std::cin >> price;
    sub.setPrice(price);

    std::cout << "������� ���������� ����: ";
    int days;
    std::cin >> days;
    sub.setDays(days);

    subscriptions.push_back(sub);
    std::cout << "�������� \"" << sub.getName() << "\" �������.\n";
}

void Admin::readSubscriptions() {
    std::cout << "\n������ ��������:\n";
    for (const auto& sub : subscriptions) {
        std::cout << sub << "\n";
    }
}

void Admin::updateSubscription() {
    // ������ ���������� ��������
    std::cout << "������� ���������� �������� �� �����������.\n";
}

void Admin::deleteSubscription() {
    // ������ �������� ��������
    std::cout << "������� �������� �������� �� �����������.\n";
}

void Admin::createPlace() {
    Place place;
    std::cout << "������� �������� ����: ";
    std::string name;
    std::cin >> name;
    place.setName(name);

    std::cout << "������� ����� ����: ";
    std::string address;
    std::cin >> address;
    place.setAddress(address);

    std::cout << "������� ���� ������: ";
    std::string hours;
    std::cin >> hours;
    place.setHours(hours);

    places.push_back(place);
    std::cout << "��� \"" << place.getName() << "\" ������.\n";
}

void Admin::readPlaces() {
    std::cout << "\n������ �����:\n";
    for (const auto& place : places) {
        std::cout << place << "\n";
    }
}

void Admin::updatePlace() {
    // ������ ���������� ����
    std::cout << "������� ���������� ���� �� �����������.\n";
}

void Admin::deletePlace() {
    // ������ �������� ����
    std::cout << "������� �������� ���� �� �����������.\n";
}

void Admin::showMenu() const {
    int choice = 0;
    do {
        std::cout << "\n���� ��������������\n";
        std::cout << "1. ���������� ������\n";
        std::cout << "2. ���������� ����������\n";
        std::cout << "3. �����\n";
        std::cout << "�������� �����: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            managePlaces();
            break;
        case 2:
            manageSubscriptions();
            break;
        case 3:
            std::cout << "����� �� �������...\n";
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 3);
}