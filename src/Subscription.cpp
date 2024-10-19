#include "Subscription.h"
#include <iostream>

void Subscription::saveToFile(std::ofstream& ofs) const {
    ofs << id << ' ' << name << ' ' << price << ' ' << days << ' ' << activated << '\n';
}

void Subscription::loadFromFile(std::ifstream& ifs) {
    ifs >> id >> name >> price >> days >> activated;
}

void Subscription::comparePrices(const std::vector<std::shared_ptr<Subscription>>& services) const {
    if (services.size() < 2) {
        std::cout << "��� ��������� ��� ����� ������� ��� ��������.\n";
        return;
    }

    std::string name1, name2;
    std::cout << "������� �������� ������ ��������: ";
    std::cin >> name1;
    std::cout << "������� �������� ������ ��������: ";
    std::cin >> name2;

    std::shared_ptr<Subscription> sub1 = nullptr, sub2 = nullptr;

    for (const auto& sub : services) {
        if (sub->getName() == name1) {
            sub1 = sub;
        }
        else if (sub->getName() == name2) {
            sub2 = sub;
        }
    }

    if (sub1 && sub2) {
        if (*sub1 == *sub2) {
            std::cout << "�������� \"" << name1 << "\" � \"" << name2 << "\" ����� ���������� ����.\n";
        }
        else if (*sub1 > *sub2) {
            std::cout << "�������� \"" << name1 << "\" ������ �������� \"" << name2 << "\".\n";
        }
        else {
            std::cout << "�������� \"" << name2 << "\" ������ �������� \"" << name1 << "\".\n";
        }
    }
    else {
        std::cout << "���� ��� ��� �������� �� �������.\n";
    }
}
