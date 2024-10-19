#include "Admin.h"
#include "Place.h"
#include "Subscription.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

using namespace std;

void Admin::saveAllPlacesToFile(const vector<Place>& places) {
    ofstream ofs("places.txt");
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи мест!" << endl;
        return;
    }
    for (const auto& place : places) {
        ofs << place << endl;
    }
    ofs.close();
}

void Admin::saveAllSubscriptionsToFile(const vector<shared_ptr<Subscription>>& subscriptions) {
    ofstream ofs("subscriptions.txt");
    if (!ofs) {
        cerr << "Ошибка открытия файла для записи подписок!" << endl;
        return;
    }
    for (const auto& subscription : subscriptions) {
        ofs << *subscription << endl;  // Предполагается перегруженный оператор <<
    }
    ofs.close();
}

void Admin::loadAllPlacesFromFile(vector<Place>& places) {
    ifstream ifs("places.txt");
    if (!ifs) {
        cerr << "Ошибка открытия файла для чтения мест!" << endl;
        return;
    }

    Place place;
    while (ifs >> place) { // Перегруженный оператор >>
        places.push_back(place);
    }

    ifs.close();
    cout << "Места загружены из файла.\n";
}

void Admin::loadAllSubscriptionsFromFile(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    std::ifstream ifs("subscriptions.txt");
    if (!ifs) {
        std::cerr << "Ошибка открытия файла для чтения подписок!" << std::endl;
        return;
    }

    while (true) {
        int id, type;
        std::string name;
        double price;
        int days;

        if (!(ifs >> id >> name >> price >> days >> type)) break;

        std::shared_ptr<Subscription> sub;
        if (type == 1) {  
            int sessions;
            ifs >> sessions;
            sub = std::make_shared<LimitedSubscription>(id, name, price, days, sessions);
        }
        else if (type == 2) {  
            sub = std::make_shared<UnlimitedSubscription>(id, name, price, days);
        }

        if (sub) {
            subscriptions.push_back(sub);
        }
    }

    ifs.close();
}

void Admin::showMenu(vector<Place>& places, vector<shared_ptr<Subscription>>& subscriptions) {
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
            managePlaces(places, subscriptions);
            break;
        case 2:
            manageSubscriptions(subscriptions);
            break;
        case 3:
            cout << "Выход из системы...\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 3);
}

void Admin::managePlaces(vector<Place>& places, vector<shared_ptr<Subscription>>& subscriptions) {
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
            newPlace.create(places, subscriptions);
            cout << "Новый зал добавлен." << endl;
            break;
        }
        case 2:
            Place().read(places);
            break;
        case 3:
            Place().update(places, subscriptions);
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

void Admin::manageSubscriptions(vector<shared_ptr<Subscription>>& subscriptions) {
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
        case 1:
            createSubscription(subscriptions);
            break;
        case 2:
            readSubscriptions(subscriptions);
            break;
        case 3:
            updateSubscription(subscriptions);
            break;
        case 4:
            deleteSubscription(subscriptions);
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

void Admin::createSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    int id, type;
    std::string name;
    double price;
    int days;

    std::cout << "Введите ID подписки: ";
    std::cin >> id;
    std::cout << "Введите название подписки: ";
    std::cin >> name;
    std::cout << "Введите цену подписки: ";
    std::cin >> price;
    std::cout << "Введите количество дней: ";
    std::cin >> days;

    std::cout << "Выберите тип подписки (1 - Ограниченная, 2 - Безлимитная): ";
    std::cin >> type;

    std::shared_ptr<Subscription> newSub;
    if (type == 1) {
        int sessions;
        std::cout << "Введите количество занятий: ";
        std::cin >> sessions;
        newSub = std::make_shared<LimitedSubscription>(id, name, price, days, sessions);
    }
    else if (type == 2) {
        newSub = std::make_shared<UnlimitedSubscription>(id, name, price, days);
    }
    else {
        std::cout << "Некорректный тип подписки.\n";
        return;
    }

    subscriptions.push_back(newSub);
}

void Admin::updateSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    std::cout << "Введите ID подписки для обновления: ";
    int id;
    std::cin >> id;

    for (auto& subscription : subscriptions) {
        if (subscription->getId() == id) {
            std::string name;
            double newPrice;
            int days;

            std::cout << "Введите новое название подписки: ";
            std::cin >> name;
            std::cout << "Введите новую цену подписки: ";
            std::cin >> newPrice;
            std::cout << "Введите новое количество дней: ";
            std::cin >> days;

            subscription->setName(name);
            subscription->setPrice(newPrice);
            subscription->setDays(days);
            std::cout << "Подписка успешно обновлена." << std::endl;
            return;
        }
    }
    std::cout << "Подписка не найдена." << std::endl;
}

void Admin::deleteSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    std::cout << "Введите ID подписки для удаления: ";
    int id;
    std::cin >> id;

    auto it = std::remove_if(subscriptions.begin(), subscriptions.end(),
        [&](const std::shared_ptr<Subscription>& subscription) {
            return subscription->getId() == id;
        });

    if (it != subscriptions.end()) {
        subscriptions.erase(it, subscriptions.end());
        std::cout << "Подписка успешно удалена." << std::endl;
    }
    else {
        std::cout << "Подписка не найдена." << std::endl;
    }
}

void Admin::readSubscriptions(const std::vector<std::shared_ptr<Subscription>>& subscriptions) const {
    std::cout << "Список подписок:\n";
    for (const auto& subscription : subscriptions) {
        std::cout << "ID: " << subscription->getId() << ", Название: " << subscription->getName()
            << ", Цена: " << subscription->getPrice() << ", Дней: " << subscription->getDays() << std::endl;
    }
}
