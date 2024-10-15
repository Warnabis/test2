#include "Admin.h"
#include "Place.h"
#include "Subscription.h"
#include <iostream>

using namespace std;

void Admin::showMenu(vector<Place>& places, vector<Subscription>& subscriptions) {
    int choice;
    do {
        cout << "\nМеню администратора\n";
        cout << "1. Управление залами\n";
        cout << "2. Управление подписками\n";
        cout << "3. Выйти\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            managePlaces(places); // Переход в подменю работы с залами
            break;
        case 2:
            manageSubscriptions(subscriptions); // Переход в подменю работы с подписками
            break;
        case 3:
            cout << "Выход из системы...\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 3);
}

void Admin::managePlaces(vector<Place>& places) {
    int choice;
    do {
        cout << "\nУправление залами\n";
        cout << "1. Добавить новый зал\n";
        cout << "2. Просмотреть все залы\n";
        cout << "3. Обновить данные зала\n";
        cout << "4. Удалить зал\n";
        cout << "5. Сохранить данные о залах в файл\n";
        cout << "6. Вернуться в меню\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Place newPlace;
            newPlace.create(places);
            break;
        }
        case 2:
            Place().read(places);
            break;
        case 3:
            Place().update(places);
            break;
        case 4:
            Place().deletes(places);
            break;
        case 5:
            saveAllPlacesToFile(places);
            break;
        case 6:
            cout << "Возвращение в главное меню...\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 6);
}

void Admin::manageSubscriptions(vector<Subscription>& subscriptions) {
    int choice;
    do {
        cout << "\nУправление подписками\n";
        cout << "1. Добавить новую подписку\n";
        cout << "2. Просмотреть все подписки\n";
        cout << "3. Обновить данные подписки\n";
        cout << "4. Удалить подписку\n";
        cout << "5. Сохранить данные о подписках в файл\n";
        cout << "6. Вернуться в меню\n";
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Subscription newSubscription;
            newSubscription.create(subscriptions);
            break;
        }
        case 2:
            Subscription().read(subscriptions);
            break;
        case 3:
            Subscription().update(subscriptions);
            break;
        case 4:
            Subscription().deletes(subscriptions);
            break;
        case 5:
            saveAllSubscriptionsToFile(subscriptions);
            break;
        case 6:
            cout << "Возвращение в главное меню...\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 6);
}
