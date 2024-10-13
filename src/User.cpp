#include "User.h"
#include <iostream>

void User::showMenu() {
    int choice = 0;
    do {
        std::cout << "\n���� ������������\n";
        std::cout << "1. ����������� ������ �����\n";
        std::cout << "2. ���������� ��������\n";
        std::cout << "3. �����\n";
        std::cout << "�������� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewPlaces();
            break;
        case 2:
            viewSubscriptions();
            break;
        case 3:
            std::cout << "����� �� �������...\n";
            break;
        default:
            std::cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 3);
}

void User::viewSubscriptions() const {
    std::cout << "�������� ��������...\n";
    for (const auto& sub : subscriptions) {
        std::cout << sub.getName() << " - �������: " << (sub.isActivated() ? "��" : "���") << "\n";
    }
}

void User::viewPlaces() const {
    std::cout << "�������� ������ �����...\n";
    for (const auto& place : places) {
        std::cout << place.getName() << " - �����: " << place.getAddress() << " - ��������: " << (place.isActivated() ? "��" : "���") << "\n";
    }
}