#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <memory> 

#include "Admin.h"
#include "User.h"
#include "Place.h"
#include "Subscription.h"
#include "LimitedSubscription.h"
#include "UnlimitedSubscription.h"
#include "SubscriptionList.h"   
#include "Functions.h"

using namespace std;

void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions);
void saveAllPlacesToFile(const std::vector<Place>& places);
void loadAllSubscriptionsFromFile(std::vector<std::shared_ptr<Subscription>>& subscriptions);
void saveAllSubscriptionsToFile(const std::vector<std::shared_ptr<Subscription>>& subscriptions);

void saveAllSubscriptionsToFile(const vector<shared_ptr<Subscription>>& subscriptions) {
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

void loadAllSubscriptionsFromFile(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
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

int main() {
    setlocale(LC_ALL, "rus");
    vector<Place> places;
    vector<shared_ptr<Subscription>> subscriptions; // Изменено на shared_ptr

    char loadFromFile;
    cout << "Считывать данные из файла? (y/n): ";
    cin >> loadFromFile;
    cin.ignore();

    if (loadFromFile == 'y' || loadFromFile == 'Y') {
        cout << endl;
        loadAllSubscriptionsFromFile(subscriptions);
        loadAllPlacesFromFile(places, subscriptions);
        wait();
    }

    int userType;
    cout << "Выберите тип пользователя:\n";
    cout << "1. Администратор\n";
    cout << "2. Обычный пользователь\n";
    cout << "Ваш выбор: ";
    cin >> userType;

    if (userType == 1) {
        string inputLogin, inputPassword;
        cout << "Введите логин: ";
        cin >> inputLogin;
        cout << "Введите пароль: ";
        cin >> inputPassword;

        Admin admin;

        if (inputLogin == admin.getLogin() && inputPassword == admin.getPassword()) {
            cout << "Успешный вход!" << endl;
            wait();
            admin.showMenu(places, subscriptions); // Изменено для использования shared_ptr

            saveAllPlacesToFile(places);
            saveAllSubscriptionsToFile(subscriptions);
        }
        else {
            cout << "Неверный логин или пароль!" << endl;
            wait();
        }
    }
    else if (userType == 2) {
        string inputLogin, inputPassword;
        cout << "Введите логин: ";
        cin >> inputLogin;
        cout << "Введите пароль: ";
        cin >> inputPassword;

        User user;

        if (inputLogin == user.getLogin() && inputPassword == user.getPassword()) {
            cout << "Успешный вход!" << endl;
            wait();
            user.showMenu(places, subscriptions); 
        }
        else {
            cout << "Неверный логин или пароль!" << endl;
            wait();
        }
    }
    else {
        cout << "Неверный выбор! Программа завершена." << endl;
        wait();
    }

    return 0;
}

