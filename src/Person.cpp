#include "Person.h"

// Реализация конструктора
Person::Person(const std::string& login, const std::string& password)
    : login(login), password(password) {}

// Реализация остальных методов
std::string Person::getLogin() const {
    return login;
}

std::string Person::getPassword() const {
    return password;
}