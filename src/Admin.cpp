#include "Admin.h"
#include "Place.h"
#include "Subscription.h"
#include <iostream>

using namespace std;

void Admin::showMenu(vector<Place>& places, vector<Subscription>& subscriptions) {
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
            managePlaces(places); // ������� � ������� ������ � ������
            break;
        case 2:
            manageSubscriptions(subscriptions); // ������� � ������� ������ � ����������
            break;
        case 3:
            cout << "����� �� �������...\n";
            break;
        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    } while (choice != 3);
}

void Admin::managePlaces(vector<Place>& places) {
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
            newPlace.create(places);
            break;
        }
        case 2:
            Place().read(places);
            break;
        case 3:
            Place().update(places);
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

void Admin::manageSubscriptions(vector<Subscription>& subscriptions) {
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
        case 1: {
            Subscription newSubscription;
            newSubscription.create(subscriptions);
            break;
        }
        case 2:
            Subscription().read(subscriptions);
            break;
        case 3:
            Subscription().update(subscriptions);
            break;
        case 4:
            Subscription().deletes(subscriptions);
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
