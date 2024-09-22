#include "Subscription.h"
#include <vector>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    std::vector<Subscription> services;
    Subscription service;
    Subscription* selectedservice = nullptr;
    int choice;

    do {
        std::cout << "\n1. Создать новый объект\n2. Вывести объект(ы)\n3. Обновить объект(ы)\n4. Удалить объект(ы)\n5. Управление тренировками (выбор, тренировка, статус)\n6. Выйти из программы\nВыберите опцию: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                service.create(services);
                break;
            case 2:
                service.read(services);
                break;
            case 3:
                service.update(services);
                break;
            case 4:
                service.deletes(services);
                break;
            case 5:
                service.workout(services, selectedservice);
                break;
            case 6:
                std::cout << "Выход из программы..." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова" << std::endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
