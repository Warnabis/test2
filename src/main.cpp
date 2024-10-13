#include "Person.h"
#include "User.h"
#include "Admin.h"
#include "Place.h"
#include "Subscription.h"
#include "Functions.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    setlocale(LC_ALL, "rus");
    std::string role;
    std::cout << "Введите вашу роль (user/admin): ";
    std::cin >> role;

    if (role == "user") {
        User user("user1", "password123");
        user.showMenu();
    }
    else if (role == "admin") {
        Admin admin("admin1", "adminpass");
        admin.showMenu();
    }
    else {
        std::cout << "Неверная роль. Программа завершена.\n";
    }

    return 0;
}