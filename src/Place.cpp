#include "Place.h"
#include <iostream>
#include <fstream>
#include <algorithm>

// ����� ��� �������� ������ ����
void Place::create(std::vector<Place>&places) const {
    std::string name, address, hours;
    std::cout << "������� �������� ����: ";
    std::cin >> name;
    std::cout << "������� ����� ����: ";
    std::cin >> address;
    std::cout << "������� ���� ������: ";
    std::cin >> hours;

    Place newPlace(name, address, hours);
    places.push_back(newPlace);
    std::cout << "��� \"" << name << "\" ��������.\n";
}

// ����� ��� ������ ���������� � �����
void Place::read(const std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "��� ��������� �����.\n";
        return;
    }

    for (const auto& place : places) {
        std::cout << "��������: " << place.getName()
            << ", �����: " << place.getAddress()
            << ", ���� ������: " << place.getHours()
            << ", �����������: " << (place.isActivated() ? "��" : "���") << "\n";

        // ������� ��������
        const auto& subs = place.getSubscriptions();
        if (!subs.empty()) {
            std::cout << "��������:\n";
            for (const auto& sub : subs) {
                std::cout << "  - " << sub.getName() << "\n"; // ��������������, ��� ���� ����� getName() � Subscription
            }
        }
    }
}

// ����� ��� ���������� ���������� � ����
void Place::update(std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "��� ����� ��� ����������.\n";
        return;
    }

    std::string name;
    std::cout << "������� �������� ���� ��� ����������: ";
    std::cin >> name;

    auto it = std::find_if(places.begin(), places.end(), [&](const Place& place) {
        return place.getName() == name;
        });

    if (it != places.end()) {
        std::cout << "������� ����� �����: ";
        std::string newAddress;
        std::cin >> newAddress;

        std::cout << "������� ����� ���� ������: ";
        std::string newHours;
        std::cin >> newHours;

        it->deactivate(); // ������, ��� ����� ������������/�������������� ���
        *it = Place(name, newAddress, newHours, it->isActivated()); // ���������� ����
        std::cout << "��� \"" << name << "\" ��������.\n";
    }
    else {
        std::cout << "��� � ��������� \"" << name << "\" �� ������.\n";
    }
}

// ����� ��� �������� ����
void Place::deletes(std::vector<Place>& places) const {
    if (places.empty()) {
        std::cout << "��� ����� ��� ��������.\n";
        return;
    }

    std::string name;
    std::cout << "������� �������� ���� ��� ��������: ";
    std::cin >> name;

    auto it = std::remove_if(places.begin(), places.end(), [&](const Place& place) {
        return place.getName() == name;
        });

    if (it != places.end()) {
        places.erase(it, places.end());
        std::cout << "��� \"" << name << "\" ������.\n";
    }
    else {
        std::cout << "��� � ��������� \"" << name << "\" �� ������.\n";
    }
}

// ����� ��� ���������� ���� � ����
void Place::saveToFile(std::ofstream& ofs, const std::vector<Place>& items) const {
    for (const auto& place : items) {
        ofs << place.getName() << "\n"
            << place.getAddress() << "\n"
            << place.getHours() << "\n"
            << place.isActivated() << "\n";
    }
}

// ����� ��� �������� ����� �� �����
void Place::loadFromFile(std::ifstream& ifs, std::vector<Place>& items) {
    std::string name, address, hours;
    bool activated;

    while (std::getline(ifs, name)) {
        std::getline(ifs, address);
        std::getline(ifs, hours);
        ifs >> activated;
        ifs.ignore(); // ���������� ������ ����� ������ ����� ������ bool

        items.emplace_back(name, address, hours, activated);
    }
}