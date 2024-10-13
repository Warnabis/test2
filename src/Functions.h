#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <vector>

template <typename T>
class FileOperations {
public:
    virtual void saveToFile(std::ofstream& ofs, const std::vector<T>& items) const = 0;
    virtual void loadFromFile(std::ifstream& ifs, std::vector<T>& items) = 0;
};

void wait();


#endif 
