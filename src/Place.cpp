#include "Place.h"

void Place::savePlacesToFile(std::ofstream& ofs) const {
    ofs << name << std::endl;
    ofs << address << std::endl;
    ofs << hours << std::endl;
    ofs << activated << std::endl;
    ofs << subscriptions.size() << std::endl;
    for (const auto& subscription : subscriptions) {
        ofs << subscription->getName() << std::endl; // Используем оператор -> для доступа к методу
    }
}

void Place::loadPlacesFromFile(std::ifstream& ifs, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions) {
    getline(ifs, name);
    getline(ifs, address);
    getline(ifs, hours);
    ifs >> activated;
    size_t subCount;
    ifs >> subCount;
    ifs.ignore(); // Игнорируем символ новой строки
    subscriptions.clear();

    for (size_t i = 0; i < subCount; i++) {
        std::string subscriptionName;
        getline(ifs, subscriptionName);

        auto it = std::find_if(existingSubscriptions.begin(), existingSubscriptions.end(),
            [&subscriptionName](const std::shared_ptr<Subscription>& sub) {
                return sub->getName() == subscriptionName; // Используем оператор -> для доступа к методу
            });

        if (it != existingSubscriptions.end()) {
            subscriptions.push_back(*it); // Добавляем указатель на существующую подписку
        }
        else {
            std::cout << "Подписка с именем " << subscriptionName << " не найдена.\n";
            return;
        }
    }
}

void Place::create(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions) const {
    Place newPlace;
    std::cout << "Введите название зала: ";
    std::cin >> newPlace.name;

    std::cout << "Введите адрес зала: ";
    std::cin >> newPlace.address;

    std::cout << "Введите время работы (формат HH:MM-HH:MM): ";
    std::cin >> newPlace.hours;

    std::cout << "Зал активен? (1 - да, 0 - нет): ";
    std::cin >> newPlace.activated;
    std::cin.ignore();

    std::vector<std::shared_ptr<Subscription>> selectedSubscriptions;
    std::string subscriptionName;

    while (true) {
        std::cout << "Введите название подписки (или 'end' для завершения): ";
        std::getline(std::cin, subscriptionName);

        if (subscriptionName == "end") {
            break;
        }

        auto subIt = std::find_if(subscriptions.begin(), subscriptions.end(),
            [&subscriptionName](const std::shared_ptr<Subscription>& sub) {
                return sub->getName() == subscriptionName; // Используем оператор -> для доступа к методу
            });
        if (subIt != subscriptions.end()) {
            selectedSubscriptions.push_back(*subIt); // Добавляем указатель на выбранную подписку
        }
        else {
            std::cout << "Подписка с именем '" << subscriptionName << "' не найдена!\n";
        }
    }

    newPlace.subscriptions = selectedSubscriptions;
    places.push_back(newPlace);
}

void Place::read(const std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "Нет объектов для отображения." << std::endl;
        return;
    }

    for (size_t i = 0; i < places.size(); i++) {
        std::cout << "Объект " << i + 1 << ":\n" << places[i] << std::endl;
    }
}

void Place::update(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& availableSubscriptions) const {
    if (places.empty()) {
        std::cout << "Нет объектов для обновления." << std::endl;
        return;
    }

    int index;
    std::cout << "Введите номер зала для обновления: ";
    std::cin >> index;

    if (index <= 0 || index > places.size()) {
        std::cout << "Неверный номер зала." << std::endl;
        return;
    }

    Place& placeToUpdate = places[index - 1];

    std::string name, address, hours;
    std::cout << "Введите новое название зала (оставьте пустым для сохранения старого): ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Введите новый адрес зала (оставьте пустым для сохранения старого): ";
    std::getline(std::cin, address);
    std::cout << "Введите новые часы работы (оставьте пустым для сохранения старых): ";
    std::getline(std::cin, hours);

    if (!name.empty()) placeToUpdate.setName(name);
    if (!address.empty()) placeToUpdate.setAddress(address);
    if (!hours.empty()) placeToUpdate.setHours(hours);

    int numSubscriptions;
    std::cout << "Сколько подписок вы хотите добавить? ";
    std::cin >> numSubscriptions;
    for (int i = 0; i < numSubscriptions; i++) {
        std::cout << "Доступные подписки:\n";
        for (size_t j = 0; j < availableSubscriptions.size(); j++) {
            std::cout << j + 1 << ". " << availableSubscriptions[j]->getName() << "\n"; // Используем оператор -> для доступа к методу
        }
        int subIndex;
        std::cout << "Выберите подписку по номеру: ";
        std::cin >> subIndex;
        if (subIndex > 0 && subIndex <= availableSubscriptions.size()) {
            placeToUpdate.addSubscription(availableSubscriptions[subIndex - 1]); // Добавляем указатель на выбранную подписку
        }
        else {
            std::cout << "Неверный номер подписки." << std::endl;
        }
    }

    std::cout << "Зал обновлён успешно.\n";
}

void Place::deletes(std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "Нет объектов для удаления." << std::endl;
        return;
    }

    int index;
    std::cout << "Введите номер зала для удаления: ";
    std::cin >> index;

    if (index <= 0 || index > places.size()) {
        std::cout << "Неверный номер зала." << std::endl;
        return;
    }

    places.erase(places.begin() + (index - 1));
    std::cout << "Зал удалён успешно.\n";
}

void saveAllPlacesToFile(const std::vector<Place>& places) {
    std::ofstream ofs("places.txt");
    if (!ofs) {
        std::cout << "Ошибка открытия файла для записи!\n";
        return;
    }

    for (const auto& place : places) {
        place.savePlacesToFile(ofs);
    }

    ofs.close();
    std::cout << "Данные о залах сохранены в файл.\n";
}

void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions) {
    std::ifstream ifs("places.txt");
    if (!ifs) {
        std::cout << "Ошибка открытия файла для чтения!\n";
        return;
    }

    places.clear();

    while (!ifs.eof()) {
        Place tempPlace;
        tempPlace.loadPlacesFromFile(ifs, existingSubscriptions);

        if (ifs.fail() && !ifs.eof()) {
            std::cout << "Ошибка при загрузке зала.\n";
            break;
        }

        places.push_back(tempPlace);
    }

    ifs.close();
    std::cout << "Данные о залах загружены из файла.\n";
}
