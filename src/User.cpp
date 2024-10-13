#include "User.h"
#include <iostream>

void User::showMenu() {
    int choice = 0;
    do {
        std::cout << "\nМеню пользователя\n";
        std::cout << "1. Просмотреть список залов\n";
        std::cout << "2. Посмотреть подписки\n";
        std::cout << "3. Выйти\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewPlaces();
            break;
        case 2:
            viewSubscriptions();
            break;
        case 3:
            std::cout << "Выход из системы...\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 3);
}

void User::viewSubscriptions() const {
    std::cout << "Просмотр подписок...\n";
    for (const auto& sub : subscriptions) {
        std::cout << sub.getName() << " - Активна: " << (sub.isActivated() ? "Да" : "Нет") << "\n";
    }
}

void User::viewPlaces() const {
    std::cout << "Просмотр списка залов...\n";
    for (const auto& place : places) {
        std::cout << place.getName() << " - Адрес: " << place.getAddress() << " - Работает: " << (place.isActivated() ? "Да" : "Нет") << "\n";
    }
}