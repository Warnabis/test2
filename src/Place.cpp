#include "Place.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// Метод для создания нового зала
void Place::create(std::vector<Place>&places) const {
    std::string name, address, hours;
    std::cout << "Введите название зала: ";
    std::cin >> name;
    std::cout << "Введите адрес зала: ";
    std::cin >> address;
    std::cout << "Введите часы работы: ";
    std::cin >> hours;

    Place newPlace(name, address, hours);
    places.push_back(newPlace);
    std::cout << "Зал \"" << name << "\" добавлен.\n";
}

// Метод для чтения информации о залах
void Place::read(const std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "Нет доступных залов.\n";
        return;
    }

    for (const auto& place : places) {
        std::cout << "Название: " << place.getName()
            << ", Адрес: " << place.getAddress()
            << ", Часы работы: " << place.getHours()
            << ", Активирован: " << (place.isActivated() ? "Да" : "Нет") << "\n";

        // Выводим подписки
        const auto& subs = place.getSubscriptions();
        if (!subs.empty()) {
            std::cout << "Подписки:\n";
            for (const auto& sub : subs) {
                std::cout << "  - " << sub.getName() << "\n"; // Предполагается, что есть метод getName() в Subscription
            }
        }
    }
}

// Метод для обновления информации о зале
void Place::update(std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "Нет залов для обновления.\n";
        return;
    }

    std::string name;
    std::cout << "Введите название зала для обновления: ";
    std::cin >> name;

    auto it = std::find_if(places.begin(), places.end(), [&](const Place& place) {
        return place.getName() == name;
        });

    if (it != places.end()) {
        std::cout << "Введите новый адрес: ";
        std::string newAddress;
        std::cin >> newAddress;

        std::cout << "Введите новые часы работы: ";
        std::string newHours;
        std::cin >> newHours;

        it->deactivate(); // Пример, как можно активировать/деактивировать зал
        *it = Place(name, newAddress, newHours, it->isActivated()); // Обновление зала
        std::cout << "Зал \"" << name << "\" обновлен.\n";
    }
    else {
        std::cout << "Зал с названием \"" << name << "\" не найден.\n";
    }
}

// Метод для удаления зала
void Place::deletes(std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "Нет залов для удаления.\n";
        return;
    }

    std::string name;
    std::cout << "Введите название зала для удаления: ";
    std::cin >> name;

    auto it = std::remove_if(places.begin(), places.end(), [&](const Place& place) {
        return place.getName() == name;
        });

    if (it != places.end()) {
        places.erase(it, places.end());
        std::cout << "Зал \"" << name << "\" удален.\n";
    }
    else {
        std::cout << "Зал с названием \"" << name << "\" не найден.\n";
    }
}

// Метод для сохранения зала в файл
void Place::saveToFile(std::ofstream& ofs, const std::vector<Place>& items) const {
    for (const auto& place : items) {
        ofs << place.getName() << "\n"
            << place.getAddress() << "\n"
            << place.getHours() << "\n"
            << place.isActivated() << "\n";
    }
}

// Метод для загрузки залов из файла
void Place::loadFromFile(std::ifstream& ifs, std::vector<Place>& items) {
    std::string name, address, hours;
    bool activated;

    while (std::getline(ifs, name)) {
        std::getline(ifs, address);
        std::getline(ifs, hours);
        ifs >> activated;
        ifs.ignore(); // игнорируем символ новой строки после чтения bool

        items.emplace_back(name, address, hours, activated);
    }
}