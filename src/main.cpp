#include <iostream>
#include <vector>
#include "Admin.h"
#include "User.h"   
#include "Place.h"
#include "Subscription.h"
#include "Functions.h"

using namespace std;

int main() {
    vector<Place> places;
    vector<Subscription> subscriptions;

    loadAllPlacesFromFile(places);
    loadAllSubscriptionsFromFile(subscriptions);

    int userType;
    cout << "Выберите тип пользователя:\n";
    cout << "1. Администратор\n";
    cout << "2. Обычный пользователь\n";
    cout << "Ваш выбор: ";
    cin >> userType;

    if (userType == 1) {
        // Авторизация для администратора
        string login, password;
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;

        // Создаем администратора с введенными данными
        Admin admin(login, password);
        // Запуск меню администратора
        admin.showMenu(places, subscriptions);

        // Сохранение данных в файлы после работы
        saveAllPlacesToFile(places);
        saveAllSubscriptionsToFile(subscriptions);
    }
    else if (userType == 2) {
        // Авторизация для пользователя
        string login, password;
        cout << "Введите логин: ";
        cin >> login;
        cout << "Введите пароль: ";
        cin >> password;

        // Создаем пользователя с введенными данными
        User user(login, password);
        // Запуск меню пользователя
        user.showMenu(places, subscriptions);
    }
    else {
        cout << "Неверный выбор! Программа завершена." << endl;
    }

    return 0;
}
