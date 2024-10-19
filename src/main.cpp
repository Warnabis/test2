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
        cerr << "������ �������� ����� ��� ������ ��������!" << endl;
        return;
    }
    for (const auto& subscription : subscriptions) {
        ofs << *subscription << endl;  // �������������� ������������� �������� <<
    }
    ofs.close();
}

void loadAllSubscriptionsFromFile(std::vector<std::shared_ptr<Subscription>>& subscriptions) {
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

int main() {
    setlocale(LC_ALL, "rus");
    vector<Place> places;
    vector<shared_ptr<Subscription>> subscriptions; // �������� �� shared_ptr

    char loadFromFile;
    cout << "��������� ������ �� �����? (y/n): ";
    cin >> loadFromFile;
    cin.ignore();

    if (loadFromFile == 'y' || loadFromFile == 'Y') {
        cout << endl;
        loadAllSubscriptionsFromFile(subscriptions);
        loadAllPlacesFromFile(places, subscriptions);
        wait();
    }

    int userType;
    cout << "�������� ��� ������������:\n";
    cout << "1. �������������\n";
    cout << "2. ������� ������������\n";
    cout << "��� �����: ";
    cin >> userType;

    if (userType == 1) {
        string inputLogin, inputPassword;
        cout << "������� �����: ";
        cin >> inputLogin;
        cout << "������� ������: ";
        cin >> inputPassword;

        Admin admin;

        if (inputLogin == admin.getLogin() && inputPassword == admin.getPassword()) {
            cout << "�������� ����!" << endl;
            wait();
            admin.showMenu(places, subscriptions); // �������� ��� ������������� shared_ptr

            saveAllPlacesToFile(places);
            saveAllSubscriptionsToFile(subscriptions);
        }
        else {
            cout << "�������� ����� ��� ������!" << endl;
            wait();
        }
    }
    else if (userType == 2) {
        string inputLogin, inputPassword;
        cout << "������� �����: ";
        cin >> inputLogin;
        cout << "������� ������: ";
        cin >> inputPassword;

        User user;

        if (inputLogin == user.getLogin() && inputPassword == user.getPassword()) {
            cout << "�������� ����!" << endl;
            wait();
            user.showMenu(places, subscriptions); 
        }
        else {
            cout << "�������� ����� ��� ������!" << endl;
            wait();
        }
    }
    else {
        cout << "�������� �����! ��������� ���������." << endl;
        wait();
    }

    return 0;
}

