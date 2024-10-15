#include "Place.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void Place::saveToFile(ofstream& ofs) const {
    ofs << name << endl;
    ofs << address << endl;
    ofs << hours << endl;
    ofs << activated << endl;
    ofs << subscriptions.size() << endl; 
    for (const auto& sub : subscriptions) {
        sub.saveToFile(ofs); 
    }
}


void Place::loadFromFile(ifstream& ifs) {
    getline(ifs, name);
    getline(ifs, address);
    getline(ifs, hours);
    ifs >> activated;
    size_t subCount;
    ifs >> subCount;
    ifs.ignore();
    subscriptions.clear(); 
    for (size_t i = 0; i < subCount; i++) {
        Subscription sub;
        sub.loadFromFile(ifs);  
        subscriptions.push_back(sub);
    }
}


void Place::addSubscription(const Subscription& sub) {
    subscriptions.push_back(sub);
}

void Place::create(vector<Place>& places) const {
    string placeName, placeAddress, placeHours;
    bool placeActivated;

    cout << "������� �������� ����: ";
    cin >> ws;
    getline(cin, placeName);
    cout << "������� ����� ����: ";
    getline(cin, placeAddress);
    cout << "������� ���� ������: ";
    getline(cin, placeHours);
    cout << "������������ ���? (1 - ��, 0 - ���): ";
    cin >> placeActivated;

    Place newPlace(placeName, placeAddress, placeHours, placeActivated);
    places.push_back(newPlace);

    cout << "��� ������� ������!\n";
}


void Place::read(const vector<Place>& places) const {
    if (places.empty()) {
        cout << "��� ��������� ����� ��� �����������.\n";
        return;
    }

    cout << "������ �����:\n";
    for (const auto& place : places) {
        cout << place;
        cout << "��������:\n";
        for (const auto& sub : place.getSubscriptions()) {
            cout << sub;
        }
        cout << endl;
    }
}

void Place::update(vector<Place>& places) const {
    string placeName;
    cout << "������� �������� ���� ��� ����������: ";
    cin >> ws;
    getline(cin, placeName);

    auto it = find_if(places.begin(), places.end(), [&](const Place& p) {
        return p.getName() == placeName;
        });

    if (it != places.end()) {
        string newAddress, newHours;
        bool newActivated;

        cout << "������� ����� �����: ";
        getline(cin, newAddress);
        cout << "������� ����� ���� ������: ";
        getline(cin, newHours);
        cout << "������������ ���? (1 - ��, 0 - ���): ";
        cin >> newActivated;

        it->setAddress(newAddress);
        it->setHours(newHours);
        if (newActivated) {
            it->activate();
        }
        else {
            it->deactivate();
        }

        cout << "��� ������� �������!\n";
    }
    else {
        cout << "��� � ����� ��������� �� ������.\n";
    }
}

void Place::deletes(vector<Place>& places) const {
    string placeName;
    cout << "������� �������� ���� ��� ��������: ";
    cin >> ws;
    getline(cin, placeName);

    auto it = remove_if(places.begin(), places.end(), [&](const Place& p) {
        return p.getName() == placeName;
        });

    if (it != places.end()) {
        places.erase(it, places.end());
        cout << "��� ������� �����!\n";
    }
    else {
        cout << "��� � ����� ��������� �� ������.\n";
    }
}

void saveAllPlacesToFile(const vector<Place>& places) {
    ofstream ofs("places.txt");
    if (!ofs) {
        cout << "������ �������� ����� ��� ������!\n";
        return;
    }

    for (const auto& place : places) {
        place.saveToFile(ofs);
    }

    ofs.close();
    cout << "������ � ����� ������� ��������� � ����.\n";
}

void loadAllPlacesFromFile(vector<Place>& places) {
    ifstream ifs("places.txt");
    if (!ifs) {
        cout << "������ �������� ����� ��� ������!\n";
        return;
    }

    places.clear();

    while (true) {
        Place tempPlace;
        tempPlace.loadFromFile(ifs);
        if (ifs.eof()) {
            break;
        }
        places.push_back(tempPlace);
    }

    ifs.close();
    cout << "������ � ����� ��������� �� �����.\n";
}
