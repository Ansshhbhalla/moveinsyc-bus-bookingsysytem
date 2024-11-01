#include "user.h"
#include <algorithm>
#include "bus.cpp"
#include "seat.cpp"
User::User() : username(""), password("") {}

User::User(const std::string& uname, const std::string& pwd) : username(uname), password(pwd) {}
//---------------------------------------------------------------------------------------//
void User::addBookedSeat(int seatNumber) {
    bookedSeats.push_back(seatNumber);
}

void User::removeBookedSeat(int seatNumber) {
    auto it = std::find(bookedSeats.begin(), bookedSeats.end(), seatNumber);
    if (it != bookedSeats.end()) {
        bookedSeats.erase(it);
    }
}
//--------------------------------------------------------------------------------------//
const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password;
}

const std::vector<int>& User::getBookedSeats() const {
    return bookedSeats;
}

bool User::authenticate(const std::string& enteredUsername, const std::string& enteredPassword) const {
    return (username == enteredUsername && password == enteredPassword);
}

void User::browseAvailableBuses(const std::vector<Bus>& buses, const std::string& source, const std::string& destination) {
    std::cout << "\nAvailable Buses from " << source << " to " << destination << ":\n";

    for (size_t i = 0; i < buses.size(); ++i) {
        const Bus& currentBus = buses[i];

        int percentOccupancy = (currentBus.getCurrentOccupancy() * 100 / currentBus.getTotalSeats());

        if (percentOccupancy < 60) {
            std::cout << "\033[32m";  // Set text color to green
        } else if (percentOccupancy < 90) {
            std::cout << "\033[33m";  // Set text color to yellow
        } else {
            std::cout << "\033[31m";  // Set text color to red
        }
        // Check if the bus follows the specified route
        if (currentBus.getStartingTripPlace()== source &&  currentBus.getEndingTripPlace()==destination) {
            std::cout << "Bus " << i + 1 << " - " << currentBus.getBusName() << "\n";
            std::cout << "   Route: " << currentBus.getRoute() << "\n";
            std::cout << "   Source: " << currentBus.getStartingTripPlace() << " \n";
            std::cout << "   Destination: " << currentBus.getEndingTripPlace() << " \n";
            std::cout << "   Days of Operation: " << currentBus.getDaysOfOperation() << "\n";
            std::cout << "   Total Seats: " << currentBus.getTotalSeats() << "\n";
            std::cout << "   Current Occupancy: " << currentBus.getCurrentOccupancy() << "\n";
            std::cout << "   Available Seats: " << currentBus.getTotalSeats() - currentBus.getCurrentOccupancy() << "\n";
            std::cout << "   Distance: " << currentBus.getDistance() << " km\n";
            std::cout << "   Estimated Travel Time: " << currentBus.getEstimatedTravelTime() << " hours\n";
           
            std::cout << "\n";
        }
        std::cout << "\033[0m";
    }
}

void User::checkSeatAvailability(const std::vector<Bus>& buses) {
  //  std::cout << "\nSeat Availability for " << bus.getBusName() << ":\n";

   
}

void User::saveUsersToFile(const std::vector<User>& users, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.getUsername() << " " << user.getPassword() << "\n";
        }
        file.close();
        std::cout << "Users saved to file.\n";
    } else {
        std::cerr << "Error opening file for saving users.\n";
    }
}

void User::loadUsersFromFile(std::vector<User>& users, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string username, password;
        users.clear();
        while (file >> username >> password) {
            users.emplace_back(username, password);
        }
        file.close();
        std::cout << "Users loaded from file.\n";
    } else {
        std::cerr << "Error opening file for loading users.\n";
    }
}
void User::loadBookedSeatsFromFile(const std::string& filename,User& currentUser) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for reading." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        iss >> name;
        if (name == currentUser.getUsername()) {
            int seat;
            while (iss >> seat) {
                bookedSeats.push_back(seat);
            }
            break; // Found the user, no need to continue
        }
    }
    file.close();
}

void User::saveBookedSeatsToFile(const std::string& filename,User& currentUser) {
    std::ifstream file(filename);
    std::ostringstream buffer;
    bool userFound = false;
    std::string line;

    // Read existing data and modify the line for the current user if it exists
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        iss >> name;

        if (name == currentUser.getUsername()) {
            userFound = true;
            buffer << currentUser.getUsername();
            for (int seat : bookedSeats) {
                buffer << " " << seat;
            }
            buffer << "\n";
        } else {
            buffer << line << "\n";
        }
    }
    file.close();

    // If user not found, add a new entry
    if (!userFound) {
        buffer << currentUser.getUsername();
        for (int seat : bookedSeats) {
            buffer << " " << seat;
        }
        buffer << "\n";
    }

    // Write the updated data back to the file
    std::ofstream outFile(filename, std::ios::trunc);
    outFile << buffer.str();
    outFile.close();
}
// void User::bookSeatForUser(User& currentUser, Bus& selectedBus, int seatNumber) {
//     // Attempt to book the seat
//     if (selectedBus.bookSeat(seatNumber)) {
//         // Add the seat to the user's booked seats
//         currentUser.getBookedSeats().push_back(seatNumber);
        
//         // Save updated booked seats to file
//         currentUser.saveBookedSeatsToFile("bookseats.txt",currentUser);
        
//         std::cout << "Seat " << seatNumber << " booked successfully on Bus " << selectedBus.getBusName() << ".\n";
//     } else {
//         std::cout << "Failed to book Seat " << seatNumber << ". It may already be booked.\n";
//     }
// }
// bool User::cancelBookedSeat(int seatNumber,User& currentUser) {
//     auto it = std::find( currentUser.getBookedSeats().begin(),  currentUser.getBookedSeats().end(), seatNumber);
//     if (it != bookedSeats.end()) {
//          currentUser.getBookedSeats().erase(it); // Remove the seat from bookedSeats vector
//         saveBookedSeatsToFile("bookseats.txt",currentUser); // Update the file
//         return true;
//     }
//     return false; // Seat was not found in the bookedSeats vector
// }
bool User::bookSeatForUser(User& currentUser, Bus& selectedBus, int seatNumber) {
    // Book the seat in the bus (assuming bus.bookSeat() is available)
    if (selectedBus.bookSeat(seatNumber)) {
        currentUser.addBookedSeat(seatNumber);  // Add seat to booked seats
        saveBookedSeatsToFile("bookseats.txt",currentUser); // Save to file as needed
        return true;
    }
    return false;
}

bool User::cancelBookedSeat(int seatNumber, User& currentUser,Bus& selectedBus) {
    // Cancel the seat in the bus (assuming bus.cancelSeatBooking() is available)
    if (selectedBus.cancelSeatBooking(seatNumber)) {
        currentUser.removeBookedSeat(seatNumber); // Remove seat from booked seats
        saveBookedSeatsToFile("bookseats.txt",currentUser);   // Save to file as needed
        return true;
    }
    return false;
}