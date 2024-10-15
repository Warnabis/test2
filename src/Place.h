#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include "Functions.h"
#include "Subscription.h" 

class Place : public Activation {
private:
    std::string name;
    std::string address;
    std::string hours;
    bool activated;
    std::vector<Subscription> subscriptions; 

public:
    Place(const std::string& name = "", const std::string& address = "", const std::string& hours = "", bool activated = false)
        : name(name), address(address), hours(hours), activated(activated) {}

    
    void setName(const std::string& name) { this->name = name; }
    void setAddress(const std::string& address) { this->address = address; }
    void setHours(const std::string& hours) { this->hours = hours; }

   
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getHours() const { return hours; }

    bool isActivated() const { return activated; }
    const std::vector<Subscription>& getSubscriptions() const { return subscriptions; } 

    void activate() { activated = true; }
    void deactivate() { activated = false; }

    void addSubscription(const Subscription& sub) { subscriptions.push_back(sub); } 

    void create(std::vector<Place>& places) const;
    void read(const std::vector<Place>& places) const;
    void update(std::vector<Place>& places) const;
    void deletes(std::vector<Place>& places) const;

    
    void saveToFile(std::ofstream& ofs) const;
    void loadFromFile(std::ifstream& ifs);
    void loadAllPlacesFromFile(std::vector<Place>& places);
    void saveAllPlacesToFile(const std::vector<Place>& places);

    friend std::ostream& operator<<(std::ostream& os, const Place& place) {
        os << "Название: " << place.name << "\n"
            << "Адрес: " << place.address << "\n"
            << "Часы работы: " << place.hours << "\n";
        return os;
    }
};

#endif