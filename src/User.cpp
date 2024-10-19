#include "User.h"
#include <iostream>
#include <memory>

void User::showMenu(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    // ������ ����������� ����
    int choice;
    do {
        std::cout << "1. ����������� ��������\n";
        std::cout << "2. ����������� �����\n";
        std::cout << "3. �����\n";
        std::cout << "�������� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewSubscriptions();
            break;
        case 2:
            viewPlaces();
            break;
        case 3:
            std::cout << "����� �� ����.\n";
            break;
        default:
            std::cout << "������������ �����. ���������� ��� ���.\n";
            break;
        }
    } while (choice != 3);
}

void User::viewSubscriptions() const {
    if (subscriptions.empty()) {
        std::cout << "��� �������� ��� �����������.\n";
        return;
    }

    std::cout << "���� ��������:\n";
    for (const auto& sub : subscriptions) {
        std::cout << *sub << std::endl; // ��������������, ��� �������� << ���������� ��� Subscription
    }
}

void User::viewPlaces() const {
    if (places.empty()) {
        std::cout << "��� ���� ��� �����������.\n";
        return;
    }

    std::cout << "��������� �����:\n";
    for (const auto& place : places) {
        std::cout << place << std::endl; // ��������������, ��� �������� << ���������� ��� Place
    }
}

void User::workout(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions, std::shared_ptr<Subscription>& selectedService) const {
    // ������ ��� ����������
    // ������: ������� ����� � ��������
}

void User::comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const {
    // ������ ��� ��������� ���
}

void User::displaySubscriptionDetails(const Subscription& subscription) const {
    // ������ ����������� ������� ��������
}
