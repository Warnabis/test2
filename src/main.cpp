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
    cout << "�������� ��� ������������:\n";
    cout << "1. �������������\n";
    cout << "2. ������� ������������\n";
    cout << "��� �����: ";
    cin >> userType;

    if (userType == 1) {
        // ����������� ��� ��������������
        string login, password;
        cout << "������� �����: ";
        cin >> login;
        cout << "������� ������: ";
        cin >> password;

        // ������� �������������� � ���������� �������
        Admin admin(login, password);
        // ������ ���� ��������������
        admin.showMenu(places, subscriptions);

        // ���������� ������ � ����� ����� ������
        saveAllPlacesToFile(places);
        saveAllSubscriptionsToFile(subscriptions);
    }
    else if (userType == 2) {
        // ����������� ��� ������������
        string login, password;
        cout << "������� �����: ";
        cin >> login;
        cout << "������� ������: ";
        cin >> password;

        // ������� ������������ � ���������� �������
        User user(login, password);
        // ������ ���� ������������
        user.showMenu(places, subscriptions);
    }
    else {
        cout << "�������� �����! ��������� ���������." << endl;
    }

    return 0;
}
