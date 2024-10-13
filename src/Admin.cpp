#include "Admin.h"
#include <iostream>

Admin::Admin(const std::string& login, const std::string& password)
    : Person(login, password) {}

void Admin::manageSubscriptions() {
    int choice;
    do {
        std::cout << "\nУправление подписками:\n";
        std::cout << "1. Создать подписку\n";
        std::cout << "2. Прочитать подписки\n";
        std::cout << "3. Обновить подписку\n";
        std::cout << "4. Удалить подписку\n";
        std::cout << "5. Назад в меню администратора\n";
        std::cout << "Выберите опцию: ";
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
            std::cout << "Возврат в меню администратора.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 5);
}

void Admin::managePlaces() {
    int choice;
    do {
        std::cout << "\nУправление залами:\n";
        std::cout << "1. Создать зал\n";
        std::cout << "2. Прочитать залы\n";
        std::cout << "3. Обновить зал\n";
        std::cout << "4. Удалить зал\n";
        std::cout << "5. Назад в меню администратора\n";
        std::cout << "Выберите опцию: ";
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
            std::cout << "Возврат в меню администратора.\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 5);
}

void Admin::createSubscription() {
    Subscription sub;
    std::cout << "Введите название подписки: ";
    std::string name;
    std::cin >> name;
    sub.setName(name);

    std::cout << "Введите цену подписки: ";
    float price;
    std::cin >> price;
    sub.setPrice(price);

    std::cout << "Введите количество дней: ";
    int days;
    std::cin >> days;
    sub.setDays(days);

    subscriptions.push_back(sub);
    std::cout << "Подписка \"" << sub.getName() << "\" создана.\n";
}

void Admin::readSubscriptions() {
    std::cout << "\nСписок подписок:\n";
    for (const auto& sub : subscriptions) {
        std::cout << sub << "\n";
    }
}

void Admin::updateSubscription() {
    // Логика обновления подписки
    std::cout << "Функция обновления подписки не реализована.\n";
}

void Admin::deleteSubscription() {
    // Логика удаления подписки
    std::cout << "Функция удаления подписки не реализована.\n";
}

void Admin::createPlace() {
    Place place;
    std::cout << "Введите название зала: ";
    std::string name;
    std::cin >> name;
    place.setName(name);

    std::cout << "Введите адрес зала: ";
    std::string address;
    std::cin >> address;
    place.setAddress(address);

    std::cout << "Введите часы работы: ";
    std::string hours;
    std::cin >> hours;
    place.setHours(hours);

    places.push_back(place);
    std::cout << "Зал \"" << place.getName() << "\" создан.\n";
}

void Admin::readPlaces() {
    std::cout << "\nСписок залов:\n";
    for (const auto& place : places) {
        std::cout << place << "\n";
    }
}

void Admin::updatePlace() {
    // Логика обновления зала
    std::cout << "Функция обновления зала не реализована.\n";
}

void Admin::deletePlace() {
    // Логика удаления зала
    std::cout << "Функция удаления зала не реализована.\n";
}

void Admin::showMenu() const {
    int choice = 0;
    do {
        std::cout << "\nМеню администратора\n";
        std::cout << "1. Управление залами\n";
        std::cout << "2. Управление подписками\n";
        std::cout << "3. Выйти\n";
        std::cout << "Выберите опцию: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            managePlaces();
            break;
        case 2:
            manageSubscriptions();
            break;
        case 3:
            std::cout << "Выход из системы...\n";
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 3);
}