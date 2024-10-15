#include "Subscription.h"
#include <iostream>
#include <limits>

using namespace std;

void Subscription::saveToFile(ofstream& ofs) const {
    ofs << id << endl;
    ofs << name << endl;
    ofs << price << endl;
    ofs << days << endl;
}

void Subscription::loadFromFile(ifstream& ifs) {
    ifs >> id;
    ifs.ignore();
    getline(ifs, name);
    ifs >> price;
    ifs >> days;
}

void Subscription::input() {
    cout << "������� ID ������: ";
    cin >> id;
    cout << "������� �������� ������: ";
    cin >> name;
    cout << "������� ���� ������: ";
    cin >> price;
    cout << "������� ���-�� ������� � ������: ";
    cin >> days;
    cout << endl;
}

void output(const Subscription& service) {
    cout << endl << service;

}

void Subscription::create(vector<Subscription>& services) const {
    Subscription newservice;
    newservice.input();
    services.push_back(newservice);

    cout << "������ ������\n";
    wait();
}

void Subscription::read(const vector<Subscription>& services) const {
    if (services.empty()) {
        cout << "��� �������� ��� �����������" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "������� �������� ������ (��� \"all\" ��� ����������� ����): ";
    cin >> checkname;
    cout << endl;

    if (checkname == "all") {
        for (size_t i = 0; i < services.size(); i++) {
            cout << "������ " << i + 1 << ": ";
            output(services[i]);
            cout << endl;
        }
    }
    else {
        bool found = false;
        for (const auto& service : services) {
            if (service.name == checkname) {
                output(service);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "������ � ��������� \"" << checkname << "\" �� �������." << endl;
        }
    }
    wait();
}

void Subscription::update(vector<Subscription>& services) const {
    if (services.empty()) {
        cout << "��� �������� ��� ����������" << endl;
        return;
    }

    string checkname;
    cout << "������� �������� ������ ��� ����������: ";
    cin >> checkname;

    bool found = false;
    for (auto& service : services) {
        if (service.name == checkname) {
            service.input();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "������ � ��������� \"" << checkname << "\" �� �������" << endl;
    }
    wait();
}

void Subscription::deletes(vector<Subscription>& services) const {
    if (services.empty()) {
        cout << "��� �������� ��� ��������" << endl;
        wait();
        return;
    }

    string checkname;
    cout << "������� �������� ������ ��� �������� (��� \"all\" ��� �������� ����): ";
    cin >> checkname;

    if (checkname == "all") {
        services.clear();
        cout << "��� ������� �������" << endl;
    }
    else {
        auto it = remove_if(services.begin(), services.end(), [&](const Subscription& service) {
            return service.name == checkname;
            });
        if (it != services.end()) {
            services.erase(it, services.end());
            cout << "������ \"" << checkname << "\" �������" << endl;
        }
        else {
            cout << "������ � ��������� \"" << checkname << "\" �� �������" << endl;
        }
    }
    wait();
}

void Subscription::workout(vector<Subscription>& services, Subscription*& selectedservice) const {
    if (services.empty()) {
        cout << "��� ��������� ����� ��� ������" << endl;
        wait();
        return;
    }

    if (selectedservice == nullptr) {
       cout << "������ �� �������. �������� ������ ����� �����������" << endl;
        string checkname;
        cout << "������� �������� ������ ��� ������: ";
        cin >> checkname;

        bool found = false;
        for (auto& service : services) {
            if (service.name == checkname) {
                selectedservice = &service;
                cout << "������ \"" << selectedservice->name << "\" �������." << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "������ � ��������� \"" << checkname << "\" �� �������." << endl;
            wait();
            return;
        }
    }

    if (!(selectedservice->isActivated())) {
        cout << "��������� ������..." << endl;
        selectedservice->activate();
    }

    int choice;
    do {
        cout << "\n1. �������� ����������\n2. ��������� ������ ����������\n3. �������� ������� ������\n4. ��������� � ������� ����\n�������� �����: ";
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�������� �����. ���������� �����\n�������� �����: ";
        }

        switch (choice) {
        case 1:
            if (selectedservice->days > 0) {
                selectedservice->days--;
                cout << "���������� ���������. �������� ����: " << selectedservice->days << endl;
            }
            else {
                cout << "� ���� ������ ������ �� �������� ��������� ���� ��� ����������" << endl;
            }
            wait();
            break;

        case 2:
            cout << "��������� ������: \"" << selectedservice->name << "\"\n�������� ����: " << selectedservice->days << endl;
            wait();
            break;

        case 3:
            cout << "����� �� ������ \"" << selectedservice->name << "\"." << endl;
            selectedservice->deactivate();  
            selectedservice = nullptr;
            wait();
            return;

        case 4:
            cout << "����������� � ������� ����..." << endl;
            wait();
            break;

        default:
            cout << "�������� �����. ���������� �����" << endl;
            wait();
            break;
        }
    } while (choice != 4);
}

void Subscription::comparePrices(const vector<Subscription>& services) const {
    if (services.size() < 2) {
        cout << "��� ��������� ��� ����� ������� ��� ������." << endl;
        wait();
        return;
    }

    string checkname1;
    string checkname2;
    cout << "������� �������� ������ ������: ";
    cin >> checkname1;
    cout << "������� �������� ������ ������: ";
    cin >> checkname2;

    const Subscription* service1 = nullptr;
    const Subscription* service2 = nullptr;

    for (const auto& service : services) {
        if (service.name == checkname1) {
            service1 = &service;
        }
        else if (service.name == checkname2) {
            service2 = &service;
        }
    }

    if (service1 && service2) {
        if (*service1 == *service2) {
            cout << "������ \"" << checkname1 << "\" � \"" << checkname2 << "\" ����� ���������� ����." << endl;
        }
        else if (*service1 > *service2) {
            cout << "������ \"" << checkname1 << "\" ������ ������ \"" << checkname2 << "\"." << endl;
        }
        else {
            cout << "������ \"" << checkname2 << "\" ������ ������ \"" << checkname1 << "\"." << endl;
        }       
    }
    else {
        if (!service1) {
            cout << "������ � ��������� \"" << checkname1 << "\" �� �������." << endl;
        }
        if (!service2) {
            cout << "������ � ��������� \"" << checkname2 << "\" �� �������." << endl;
        }
    }
    wait();
}

void saveAllSubscriptionsToFile(const vector<Subscription>& subscriptions) {
    ofstream ofs("subscriptions.txt");
    if (!ofs) {
        cout << "������ �������� ����� ��� ������!\n";
        return;
    }

    for (const auto& sub : subscriptions) {
        sub.saveToFile(ofs);
    }

    ofs.close();
    cout << "������ � ��������� ������� ��������� � ����.\n";
}

void loadAllSubscriptionsFromFile(vector<Subscription>& subscriptions) {
    ifstream ifs("subscriptions.txt");
    if (!ifs) {
        cout << "������ �������� ����� ��� ������!\n";
        return;
    }

    subscriptions.clear();

    while (true) {
        Subscription tempSub;
        tempSub.loadFromFile(ifs);
        if (ifs.eof()) {
            break;
        }
        subscriptions.push_back(tempSub);
    }

    ifs.close();
    cout << "������ � ��������� ��������� �� �����.\n";
}