#include "Functions.h"
#include <iostream>

void wait() {
    std::cout << "\n������� ����� �������, ����� ����������...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    system("cls");
}