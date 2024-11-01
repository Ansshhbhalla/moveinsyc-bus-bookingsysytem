#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include "bus.h"

class User {
private:
    std::string username;
    std::string password;
    std::vector<int> bookedSeats;
    
public:
    User();
    User(const std::string& uname, const std::string& pwd);

    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const std::vector<int>& getBookedSeats() const;
    void addBookedSeat(int seatNumber);       // Adds a seat to the bookedSeats vector
    void removeBookedSeat(int seatNumber);    // Removes a seat from the bookedSeats vector
    bool authenticate(const std::string& enteredUsername, const std::string& enteredPassword) const;
    void browseAvailableBuses(const std::vector<Bus>& buses, const std::string& source, const std::string& destination);
    void checkSeatAvailability(const std::vector<Bus>& buses);
    bool bookSeat(Bus& bus, int seatNumber);
    bool cancelSeatBooking(Bus& bus, int seatNumber);
    bool cancelBookedSeat(int seatNumber,User& currentUser,Bus& selectedBus);
    bool bookSeatForUser(User& currentUser, Bus& selectedBus, int seatNumber);
    static void saveUsersToFile(const std::vector<User>& users, const std::string& filename);
    static void loadUsersFromFile(std::vector<User>& users, const std::string& filename);
    void loadBookedSeatsFromFile(const std::string& filename,User& currentUser);
    void saveBookedSeatsToFile(const std::string& filename,User& currentUser);
};

#endif // USER_H