#include "Place.h"

void Place::savePlacesToFile(std::ofstream& ofs) const {
    ofs << name << std::endl;
    ofs << address << std::endl;
    ofs << hours << std::endl;
    ofs << activated << std::endl;
    ofs << subscriptions.size() << std::endl;
    for (const auto& subscription : subscriptions) {
        ofs << subscription->getName() << std::endl; // ���������� �������� -> ��� ������� � ������
    }
}

void Place::loadPlacesFromFile(std::ifstream& ifs, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions) {
    getline(ifs, name);
    getline(ifs, address);
    getline(ifs, hours);
    ifs >> activated;
    size_t subCount;
    ifs >> subCount;
    ifs.ignore(); // ���������� ������ ����� ������
    subscriptions.clear();

    for (size_t i = 0; i < subCount; i++) {
        std::string subscriptionName;
        getline(ifs, subscriptionName);

        auto it = std::find_if(existingSubscriptions.begin(), existingSubscriptions.end(),
            [&subscriptionName](const std::shared_ptr<Subscription>& sub) {
                return sub->getName() == subscriptionName; // ���������� �������� -> ��� ������� � ������
            });

        if (it != existingSubscriptions.end()) {
            subscriptions.push_back(*it); // ��������� ��������� �� ������������ ��������
        }
        else {
            std::cout << "�������� � ������ " << subscriptionName << " �� �������.\n";
            return;
        }
    }
}

void Place::create(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& subscriptions) const {
    Place newPlace;
    std::cout << "������� �������� ����: ";
    std::cin >> newPlace.name;

    std::cout << "������� ����� ����: ";
    std::cin >> newPlace.address;

    std::cout << "������� ����� ������ (������ HH:MM-HH:MM): ";
    std::cin >> newPlace.hours;

    std::cout << "��� �������? (1 - ��, 0 - ���): ";
    std::cin >> newPlace.activated;
    std::cin.ignore();

    std::vector<std::shared_ptr<Subscription>> selectedSubscriptions;
    std::string subscriptionName;

    while (true) {
        std::cout << "������� �������� �������� (��� 'end' ��� ����������): ";
        std::getline(std::cin, subscriptionName);

        if (subscriptionName == "end") {
            break;
        }

        auto subIt = std::find_if(subscriptions.begin(), subscriptions.end(),
            [&subscriptionName](const std::shared_ptr<Subscription>& sub) {
                return sub->getName() == subscriptionName; // ���������� �������� -> ��� ������� � ������
            });
        if (subIt != subscriptions.end()) {
            selectedSubscriptions.push_back(*subIt); // ��������� ��������� �� ��������� ��������
        }
        else {
            std::cout << "�������� � ������ '" << subscriptionName << "' �� �������!\n";
        }
    }

    newPlace.subscriptions = selectedSubscriptions;
    places.push_back(newPlace);
}

void Place::read(const std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "��� �������� ��� �����������." << std::endl;
        return;
    }

    for (size_t i = 0; i < places.size(); i++) {
        std::cout << "������ " << i + 1 << ":\n" << places[i] << std::endl;
    }
}

void Place::update(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& availableSubscriptions) const {
    if (places.empty()) {
        std::cout << "��� �������� ��� ����������." << std::endl;
        return;
    }

    int index;
    std::cout << "������� ����� ���� ��� ����������: ";
    std::cin >> index;

    if (index <= 0 || index > places.size()) {
        std::cout << "�������� ����� ����." << std::endl;
        return;
    }

    Place& placeToUpdate = places[index - 1];

    std::string name, address, hours;
    std::cout << "������� ����� �������� ���� (�������� ������ ��� ���������� �������): ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "������� ����� ����� ���� (�������� ������ ��� ���������� �������): ";
    std::getline(std::cin, address);
    std::cout << "������� ����� ���� ������ (�������� ������ ��� ���������� ������): ";
    std::getline(std::cin, hours);

    if (!name.empty()) placeToUpdate.setName(name);
    if (!address.empty()) placeToUpdate.setAddress(address);
    if (!hours.empty()) placeToUpdate.setHours(hours);

    int numSubscriptions;
    std::cout << "������� �������� �� ������ ��������? ";
    std::cin >> numSubscriptions;
    for (int i = 0; i < numSubscriptions; i++) {
        std::cout << "��������� ��������:\n";
        for (size_t j = 0; j < availableSubscriptions.size(); j++) {
            std::cout << j + 1 << ". " << availableSubscriptions[j]->getName() << "\n"; // ���������� �������� -> ��� ������� � ������
        }
        int subIndex;
        std::cout << "�������� �������� �� ������: ";
        std::cin >> subIndex;
        if (subIndex > 0 && subIndex <= availableSubscriptions.size()) {
            placeToUpdate.addSubscription(availableSubscriptions[subIndex - 1]); // ��������� ��������� �� ��������� ��������
        }
        else {
            std::cout << "�������� ����� ��������." << std::endl;
        }
    }

    std::cout << "��� ������� �������.\n";
}

void Place::deletes(std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "��� �������� ��� ��������." << std::endl;
        return;
    }

    int index;
    std::cout << "������� ����� ���� ��� ��������: ";
    std::cin >> index;

    if (index <= 0 || index > places.size()) {
        std::cout << "�������� ����� ����." << std::endl;
        return;
    }

    places.erase(places.begin() + (index - 1));
    std::cout << "��� ����� �������.\n";
}

void saveAllPlacesToFile(const std::vector<Place>& places) {
    std::ofstream ofs("places.txt");
    if (!ofs) {
        std::cout << "������ �������� ����� ��� ������!\n";
        return;
    }

    for (const auto& place : places) {
        place.savePlacesToFile(ofs);
    }

    ofs.close();
    std::cout << "������ � ����� ��������� � ����.\n";
}

void loadAllPlacesFromFile(std::vector<Place>& places, const std::vector<std::shared_ptr<Subscription>>& existingSubscriptions) {
    std::ifstream ifs("places.txt");
    if (!ifs) {
        std::cout << "������ �������� ����� ��� ������!\n";
        return;
    }

    places.clear();

    while (!ifs.eof()) {
        Place tempPlace;
        tempPlace.loadPlacesFromFile(ifs, existingSubscriptions);

        if (ifs.fail() && !ifs.eof()) {
            std::cout << "������ ��� �������� ����.\n";
            break;
        }

        places.push_back(tempPlace);
    }

    ifs.close();
    std::cout << "������ � ����� ��������� �� �����.\n";
}
