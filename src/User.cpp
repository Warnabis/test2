#include "User.h"
#include <iostream>
#include <memory>

void User::showMenu(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    // Логика отображения меню
    int choice;
    do {
        std::cout << "1. Просмотреть подписки\n";
        std::cout << "2. Просмотреть места\n";
        std::cout << "3. Выход\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewSubscriptions();
            break;
        case 2:
            viewPlaces();
            break;
        case 3:
            std::cout << "Выход из меню.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Попробуйте еще раз.\n";
            break;
        }
    } while (choice != 3);
}

void User::viewSubscriptions() const {
    if (subscriptions.empty()) {
        std::cout << "Нет подписок для отображения.\n";
        return;
    }

    std::cout << "Ваши подписки:\n";
    for (const auto& sub : subscriptions) {
        std::cout << *sub << std::endl; // Предполагается, что оператор << перегружен для Subscription
    }
}

void User::viewPlaces() const {
    if (places.empty()) {
        std::cout << "Нет мест для отображения.\n";
        return;
    }

    std::cout << "Доступные места:\n";
    for (const auto& place : places) {
        std::cout << place << std::endl; // Предполагается, что оператор << перегружен для Place
    }
}

void User::workout(const std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions, std::shared_ptr<Subscription>& selectedService) const {
    // Логика для тренировки
    // Пример: выбрать место и подписку
}

void User::comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const {
    // Логика для сравнения цен
}

void User::displaySubscriptionDetails(const Subscription& subscription) const {
    // Логика отображения деталей подписки
}
