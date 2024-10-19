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
        cerr << "������ �������� ����� ��� ������ ����!" << endl;
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
        cerr << "������ �������� ����� ��� ������ ��������!" << endl;
        return;
    }
    for (const auto& subscription : subscriptions) {
        ofs << *subscription << endl;  // �������������� ������������� �������� <<
    }
    ofs.close();
}

void Admin::loadAllPlacesFromFile(vector<Place>& places) {
    ifstream ifs("places.txt");
    if (!ifs) {
        cerr << "������ �������� ����� ��� ������ ����!" << endl;
        return;
    }

    Place place;
    while (ifs >> place) { // ������������� �������� >>
        places.push_back(place);
    }

    ifs.close();
    cout << "����� ��������� �� �����.\n";
}

void Admin::loadAllSubscriptionsFromFile(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    std::ifstream ifs("subscriptions.txt");
    if (!ifs) {
        std::cerr << "������ �������� ����� ��� ������ ��������!" << std::endl;
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
        cout << "\n���� ��������������\n";
        cout << "1. ���������� ������\n";
        cout << "2. ���������� ����������\n";
        cout << "3. �����\n";
        cout << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            managePlaces(places, subscriptions);
            break;
        case 2:
            manageSubscriptions(subscriptions);
            break;
        case 3:
            cout << "����� �� �������...\n";
            break;
        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    } while (choice != 3);
}

void Admin::managePlaces(vector<Place>& places, vector<shared_ptr<Subscription>>& subscriptions) {
    int choice;
    do {
        cout << "\n���������� ������\n";
        cout << "1. �������� ����� ���\n";
        cout << "2. ����������� ��� ����\n";
        cout << "3. �������� ������ ����\n";
        cout << "4. ������� ���\n";
        cout << "5. ��������� ������ � ����� � ����\n";
        cout << "6. ��������� � ����\n";
        cout << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Place newPlace;
            newPlace.create(places, subscriptions);
            cout << "����� ��� ��������." << endl;
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
            cout << "����������� � ������� ����...\n";
            break;
        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    } while (choice != 6);
}

void Admin::manageSubscriptions(vector<shared_ptr<Subscription>>& subscriptions) {
    int choice;
    do {
        cout << "\n���������� ����������\n";
        cout << "1. �������� ����� ��������\n";
        cout << "2. ����������� ��� ��������\n";
        cout << "3. �������� ������ ��������\n";
        cout << "4. ������� ��������\n";
        cout << "5. ��������� ������ � ��������� � ����\n";
        cout << "6. ��������� � ����\n";
        cout << "�������� �����: ";
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
            cout << "����������� � ������� ����...\n";
            break;
        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    } while (choice != 6);
}

void Admin::createSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    int id, type;
    std::string name;
    double price;
    int days;

    std::cout << "������� ID ��������: ";
    std::cin >> id;
    std::cout << "������� �������� ��������: ";
    std::cin >> name;
    std::cout << "������� ���� ��������: ";
    std::cin >> price;
    std::cout << "������� ���������� ����: ";
    std::cin >> days;

    std::cout << "�������� ��� �������� (1 - ������������, 2 - �����������): ";
    std::cin >> type;

    std::shared_ptr<Subscription> newSub;
    if (type == 1) {
        int sessions;
        std::cout << "������� ���������� �������: ";
        std::cin >> sessions;
        newSub = std::make_shared<LimitedSubscription>(id, name, price, days, sessions);
    }
    else if (type == 2) {
        newSub = std::make_shared<UnlimitedSubscription>(id, name, price, days);
    }
    else {
        std::cout << "������������ ��� ��������.\n";
        return;
    }

    subscriptions.push_back(newSub);
}

void Admin::updateSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    std::cout << "������� ID �������� ��� ����������: ";
    int id;
    std::cin >> id;

    for (auto& subscription : subscriptions) {
        if (subscription->getId() == id) {
            std::string name;
            double newPrice;
            int days;

            std::cout << "������� ����� �������� ��������: ";
            std::cin >> name;
            std::cout << "������� ����� ���� ��������: ";
            std::cin >> newPrice;
            std::cout << "������� ����� ���������� ����: ";
            std::cin >> days;

            subscription->setName(name);
            subscription->setPrice(newPrice);
            subscription->setDays(days);
            std::cout << "�������� ������� ���������." << std::endl;
            return;
        }
    }
    std::cout << "�������� �� �������." << std::endl;
}

void Admin::deleteSubscription(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
    std::cout << "������� ID �������� ��� ��������: ";
    int id;
    std::cin >> id;

    auto it = std::remove_if(subscriptions.begin(), subscriptions.end(),
        [&](const std::shared_ptr<Subscription>& subscription) {
            return subscription->getId() == id;
        });

    if (it != subscriptions.end()) {
        subscriptions.erase(it, subscriptions.end());
        std::cout << "�������� ������� �������." << std::endl;
    }
    else {
        std::cout << "�������� �� �������." << std::endl;
    }
}

void Admin::readSubscriptions(const std::vector<std::shared_ptr<Subscription>>& subscriptions) const {
    std::cout << "������ ��������:\n";
    for (const auto& subscription : subscriptions) {
        std::cout << "ID: " << subscription->getId() << ", ��������: " << subscription->getName()
            << ", ����: " << subscription->getPrice() << ", ����: " << subscription->getDays() << std::endl;
    }
}
