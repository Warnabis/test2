#include "Subscription.h"
#include <conio.h>
#include <algorithm>
#include <limits>

void Subscription::wait() const {
    std::cout << "\nНажмите любую клавишу, чтобы продолжить";
    _getch();
    system("cls");
}

void Subscription::input() {
    std::cout << "Введите ID услуги: ";
    std::cin >> id;
    std::cout << "Введите название услуги: ";
    std::cin >> name;
    std::cout << "Введите цену услуги: ";
    std::cin >> price;
    std::cout << "Введите кол-во занятий в услуге: ";
    std::cin >> days;
    std::cout << std::endl;
}

void Subscription::output() const {
    std::cout << "Айди: " << id << " Имя: " << name << " Цена: " << price << " Кол-во занятий в услуге: " << days << std::endl;
}

void Subscription::create(std::vector<Subscription>& services) const {
    Subscription newservice;
    newservice.input();
    services.push_back(newservice);
    std::cout << "Объект создан\n";
    wait();
}

void Subscription::read(const std::vector<Subscription>& services) const {
    if (services.empty()) {
        std::cout << "Нет объектов для отображения" << std::endl;
        wait();
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги (или \"all\" для отображения всех): ";
    std::cin >> checkname;

    if (checkname == "all") {
        for (size_t i = 0; i < services.size(); i++) {
            std::cout << "Объект " << i + 1 << ": ";
            services[i].output();
            std::cout << std::endl;
        }
    } else {
        bool found = false;
        for (const auto& service : services) {
            if (service.name == checkname) {
                service.output();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена." << std::endl;
        }
    }
    wait();
}

void Subscription::update(std::vector<Subscription>& services) const {
    if (services.empty()) {
        std::cout << "Нет объектов для обновления" << std::endl;
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги для обновления: ";
    std::cin >> checkname;

    bool found = false;
    for (auto& service : services) {
        if (service.name == checkname) {
            service.input();
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << "Услуга с названием \"" << checkname << "\" не найдена" << std::endl;
    }
    wait();
}

void Subscription::deletes(std::vector<Subscription>& services) const {
    if (services.empty()) {
        std::cout << "Нет объектов для удаления" << std::endl;
        wait();
        return;
    }

    std::string checkname;
    std::cout << "Введите название услуги для удаления (или \"all\" для удаления всех): ";
    std::cin >> checkname;

    if (checkname == "all") {
        services.clear();
        std::cout << "Все объекты удалены" << std::endl;
    } else {
        auto iterator = std::remove_if(services.begin(), services.end(),
            [&checkname](const Subscription& service) { return service.name == checkname; });

        if (iterator != services.end()) {
            services.erase(iterator, services.end());
            std::cout << "Услуга \"" << checkname << "\" удалена" << std::endl;
        } else {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена" << std::endl;
        }
    }
    wait();
}

void Subscription::workout(std::vector<Subscription>& services, Subscription*& selectedservice) const {
    if (services.empty()) {
        std::cout << "Нет доступных услуг для выбора" << std::endl;
        wait();
        return;
    }

    if (selectedservice == nullptr) {
        std::cout << "Услуга не выбрана. Выберите услугу перед тренировкой" << std::endl;
        std::string checkname;
        std::cout << "Введите название услуги для выбора: ";
        std::cin >> checkname;

        bool found = false;
        for (auto& service : services) {
            if (service.name == checkname) {selectedservice = &service;
                std::cout << "Услуга \"" << selectedservice->name << "\" выбрана." << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Услуга с названием \"" << checkname << "\" не найдена." << std::endl;
            wait();
            return;
        }
    }

    int choice;
    do {
        std::cout << "\n1. Провести тренировку\n2. Проверить статус тренировки\n3. Отменить текущую услугу\n4. Вернуться в главное меню\nВыберите опцию: ";
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный выбор. Попробуйте снова\nВыберите опцию: ";
        }

        switch (choice) {
            case 1:
                if (selectedservice->days > 0) {
                    selectedservice->days--;
                    std::cout << "Тренировка проведена. Осталось дней: " << selectedservice->days << std::endl;
                } else {
                    std::cout << "У этой услуги больше не осталось доступных дней для тренировок" << std::endl;
                }
                wait();
                break;

            case 2:
                std::cout << "Выбранная услуга: \"" << selectedservice->name << "\"\nОсталось дней: " << selectedservice->days << std::endl;
                wait();
                break;

            case 3:
                std::cout << "Выход из услуги \"" << selectedservice->name << "\"." << std::endl;
                selectedservice = nullptr;
                wait();
                return;

            case 4:
                std::cout << "Возвращение в главное меню..." << std::endl;
                wait();
                break;

            default:
                std::cout << "Неверный выбор. Попробуйте снова" << std::endl;
                wait();
                break;
        }
    } while (choice != 4);
}
