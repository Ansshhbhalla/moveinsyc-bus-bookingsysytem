#ifndef ADMIN_H
#define ADMIN_H


#include <iostream>
#include <vector>
#include<map>
#include "bus.h"

class Admin {
private:
    const std::string adminUsername = "admin";
    const std::string adminPassword = "pass";
     std::map<int, std::pair<std::string, std::string>> routeMap;
    const std::string apiKey = "YOUR_API_KEY";   
public:

    void loadRoutesFromFile(const std::string &filename, std::map<int, std::pair<std::string, std::string>> &routeMap);
    void saveRoutesToFile(const std::string &filename,  std::map<int, std::pair<std::string, std::string>> &routeMap);
    void addRoute(int index, const std::string &source, const std::string &destination, std::map<int, std::pair<std::string, std::string>> &routeMap, const std::string& filename);
    void deleteRoute(int index, std::map<int, std::pair<std::string, std::string>> &routeMap, const std::string &filename);
    std::pair<std::string, std::string> getRouteByIndex(int index, std::map<int, std::pair<std::string, std::string>> &routeMap);
    std::map<int, std::pair<std::string, std::string>>& getRouteMap();
    void adminLogin(std::vector<Bus>& buses);
    void manageBusDetails(std::vector<Bus>& buses);
    void loadBusesFromFile(std::vector<Bus>& buses, const std::string& filename);
    void saveBusesToFile(const std::vector<Bus>& buses, const std::string& filename);
    void saveData(const std::string& fileName) const;
    bool loadData(const std::string& fileName);
    void displaySeatPattern(const std::vector<Bus>& buses);
    bool getSeatLayout(const std::string& busName, int& rows, int& spaces, int& seatsPerColumn);
    void saveToPlan(const std::string& busName, int rows, int spaces, int seatsPerColumn, const std::string& filename);
private:
    void addBus(std::vector<Bus>& buses);
    void updateBus(std::vector<Bus>& buses);
    void deleteBus(std::vector<Bus>& buses);
    void displayAllBuses(const std::vector<Bus>& buses);
    double calculateDistance(const std::string& start, const std::string& end); 
    double calculateEstimatedTravelTime(double distance);
    
};

#endif // ADMIN_H
