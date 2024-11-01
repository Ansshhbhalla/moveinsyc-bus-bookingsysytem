
#include <iostream>
#include "ErrorHandlers.h"
#include <vector>
#include <string>
#include <fstream>
#include<string>
#include <sstream>
#include <iostream>
#include "user.cpp"
#include "admin.cpp"
#include "admin.h"
#include <set>

// ANSI escape codes for text color
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET "\033[0m"


void displayMainMenu() {
    std::cout << RED;
    std::cout << "---------------------------------------------------------------------------------------------------------\n";
    std::cout << "*********************************************************************************************************\n"; // Red stars
    std::cout << BOLD << BLUE << "Welcome to Bus Booking System by Ansh" << RESET << std::endl;  
    std::cout << RED;
    std::cout << "---------------------------------------------------------------------------------------------------------\n";
    std::cout << "*********************************************************************************************************\n"; // Red stars
    std::cout << GREEN << "1. Admin\n";
    std::cout << GREEN << "2. User\n";
    std::cout << GREEN << "3. Exit\n";
    
    std::cout << GREEN << "Enter your choice: \n";
    
    std::cout << RED;
    std::cout << "---------------------------------------------------------------------------------------------------------\n";
    std::cout << "*********************************************************************************************************\n"; // Red stars
    
    
    std::cout << RESET; // Reset to default color
    
}


void adminMenu(std::vector<Bus>& buses) {
    Admin admin;
    int choice;

    do {
        int choice;

    // Define the number of stars for the border
    const int starCount = 30; 
    std::string stars(starCount, '*');

    // Print star borders
    std::cout << RED << stars << RESET << std::endl; // Top red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars

    // Print the Admin Menu header
    std::cout << BOLD << BLUE << "Admin Menu:\n" << RESET; // Bold blue heading
    
    // Print menu items in blue
    std::cout << BLUE << "1. Manage Bus Details\n" << RESET;
    std::cout << BLUE << "2. Back to Main Menu\n" << RESET;

    // Print star borders again at the end
    std::cout << RED << stars << RESET << std::endl; // Bottom red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars

    // Prompt for input
    getInput(choice, "Enter your choice: "); 

        switch (choice) {
            case 1:
                admin.adminLogin(buses);
                
                break;
            case 2:
                return ; // Exit admin menu
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}

void performUserActions(std::vector<Bus>& buses, User& currentUser) {
    int choice;

    do {
    int choice;
    // Define the number of stars for the border
    const int starCount = 30; 
    std::string stars(starCount, '*');

    // Print star borders
    std::cout << RED << stars << RESET << std::endl; // Top red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars

    // Print the User Menu header
    std::cout << BOLD << BLUE << "\nUser Menu:\n" << RESET; // Bold blue heading
    std::cout << RED << stars << RESET << std::endl; // Top red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars
    // Print menu items in blue
    std::cout << BLUE << "1. Browse Available Buses\n" << RESET;
    std::cout << BLUE << "2. Check Seat Availability\n" << RESET;
    std::cout << BLUE << "3. Book a Seat\n" << RESET;
    std::cout << BLUE << "4. Cancel Seat Booking\n" << RESET;
    std::cout << BLUE << "5. Display booked seats\n" << RESET;
    std::cout << BLUE << "6. Back to Main Menu\n" << RESET;

    // Print star borders again at the end
    std::cout << RED << stars << RESET << std::endl; // Bottom red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars

    // Prompt for input
    getInput(choice, "Enter your choice: "); 


        switch (choice) {
            case 1: {
                std::string source, destination;
                std::cout << "Enter source: ";
                std::cin >> source;
               
                getInput(destination, "Enter your choice: ");

                currentUser.browseAvailableBuses(buses, source, destination);
                break;
            }
            case 2: {
            
                admin.displaySeatPattern(buses);
                break;
            }
            case 3: {
                std::string busName;
                int seatNumber;
                std::cout << "Enter the Name of the bus: ";
                std::cin >> busName;
                getInput(seatNumber, "Enter the seat number: ");

                int busIndex=-1;
                for (size_t i = 0; i < buses.size(); ++i) {
                  if(buses[i].getBusName()==busName){
                    busIndex=i+1;
                    break;
                   }         
                }
                if(busIndex==-1){
                     std::cout << "Invalid seat number or seat already booked.\n";
                }
                //----------------------yeha----------------------------------//
               // currentUser.bookSeatForUser(currentUser, selectedBus, seatToBook);
                else if (currentUser.bookSeatForUser(currentUser, buses[busIndex-1], seatNumber)) {
                    std::cout << "Seat booked successfully!\n";
                } else {
                    std::cout << "Invalid seat number or seat already booked.\n";
                }
                currentUser.saveBookedSeatsToFile("bookseats.txt", currentUser);
                break;
            }
            case 4: {
                std::string busName;
                int  seatNumber;
                std::cout << "Enter the Name of the bus: ";
                std::cin >> busName;
                std::cout << "Enter the seat number: ";
                getInput(seatNumber, "Enter the seat number: ");
                int busIndex=-1;
                for (size_t i = 0; i < buses.size(); ++i) {
                  if(buses[i].getBusName()==busName){
                    busIndex=i+1;
                    break;
                   }         
                }
                if(busIndex==-1){
                     std::cout << "Invalid seat number or seat already booked.\n";
                }
                //-----------------------------------yeha--------------------------------------//
               else if (currentUser.cancelBookedSeat(seatNumber, currentUser,buses[busIndex-1])) {
                    std::cout << "Seat booking canceled successfully!\n";
                } else {
                    std::cout << "Invalid seat number or seat not booked.\n";
                }
                currentUser.saveBookedSeatsToFile("bookseats.txt", currentUser);
                break;
            }
            case 5: {
                // display booked seats by the current user
                std::set<int> s1;
                std::cout << "Booked Seats by " << currentUser.getUsername() << ":\n";
                const std::vector<int>& bookedSeats = currentUser.getBookedSeats();
                for(int seatNumber:bookedSeats){
                    s1.insert(seatNumber);
                }
                if (bookedSeats.empty()) {
                    std::cout << "No seats booked by " << currentUser.getUsername() << ".\n";
                } else {
                    currentUser.loadBookedSeatsFromFile("bookseats.txt", currentUser);
                    for (int seatNumber : s1) {
                        bool foundSeat = false;
                        
                        for (const Bus& bus : buses) {
                            const std::vector<Seat>& seats = bus.getSeats();

                            
                            if (seatNumber >= 1 && seatNumber <= seats.size() && seats[seatNumber - 1].isSeatBooked()) {
                                foundSeat = true;
                               std::cout << BOLD << BLUE << "Seat Information for Seat " << seatNumber << " on Bus " << bus.getBusName() << ":\n" << RESET;
                               std::cout << "   " << BOLD << BLUE << "Route: " << RESET << bus.getRoute() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Source: " << RESET << bus.getStartingTripPlace() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Destination: " << RESET << bus.getEndingTripPlace() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Days of Operation: " << RESET << bus.getDaysOfOperation() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Total Seats: " << RESET << bus.getTotalSeats() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Current Occupancy: " << RESET << bus.getCurrentOccupancy() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Available Seats: " << RESET << bus.getTotalSeats() - bus.getCurrentOccupancy() << "\n";
                               std::cout << "   " << BOLD << BLUE << "Distance: " << RESET << bus.getDistance() << " km\n";
                               std::cout << "   " << BOLD << BLUE << "Estimated Travel Time: " << RESET << bus.getEstimatedTravelTime() << " hours\n";
                               std::cout << "\n";
                                
                            }
                        }

                        if (!foundSeat) {
                            std::cout << "No seat information available for Seat " << seatNumber << ".\n";
                        }
                    }
                }
                break;
            }
            case 6:
                break; // Exit user menu
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

void userMenu(std::vector<Bus>& buses, std::vector<User>& users) {
    std::string enteredUsername, enteredPassword;
    User currentUser;

    // User login  menu
    bool foundUser = false;
    bool usernameTaken = false;

    do {
          int loginChoice;

    // Define the number of stars for the border
    const int starCount = 30; 
    std::string stars(starCount, '*');

    // Print star borders
    std::cout << RED << stars << RESET << std::endl; // Top red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars

    // Print the User Portal heading
    std::cout << BOLD << BLUE << "User Portal\n" << RESET; // Bold blue heading

    // Print login options in blue
    std::cout << BLUE << "1. Login\n" << RESET;
    std::cout << BLUE << "2. Register\n" << RESET;
    std::cout << BLUE << "3. Back to Main Menu\n" << RESET;

    // Print star borders again at the end
    std::cout << RED << stars << RESET << std::endl; // Bottom red stars
    std::cout << RED << stars << RESET << std::endl; // Second line of red stars

    // Prompt for input
    getInput(loginChoice, "Login Choice: ");
        foundUser = false;
        usernameTaken = false;

        switch (loginChoice) {
            case 1: {
                std::cout << "Enter your username: ";
                std::cin >> enteredUsername;
                std::cout << "Enter your password: ";
                std::cin >> enteredPassword;
                for (User& user : users) {
                    if (user.authenticate(enteredUsername, enteredPassword)) {
                        std::cout << "Login successful!\n";
                        currentUser = user;  // Set the current user
                        foundUser = true;
                        performUserActions(buses, currentUser);  // Call the function for user options
                        break;
                    }
                }

                if (!foundUser) {
                    std::cout << "Invalid username or password. Try again.\n";
                }
                break;
            }
            case 2: {
                
                std::cout << "Enter a new username: ";
                std::cin >> enteredUsername;
                std::cout << "Enter a new password: ";
                std::cin >> enteredPassword;

                for (const User& user : users) {
                    if (user.getUsername() == enteredUsername) {
                        usernameTaken = true;
                        break;
                    }
                }

                if (usernameTaken) {
                    std::cout << "Username already taken. Try again.\n";
                } else {
                    
                    users.push_back(User(enteredUsername, enteredPassword));
                    currentUser = users.back();  
                    std::cout << "Registration successful!\n";
                    User::saveUsersToFile(users, "users.txt");
                    performUserActions(buses, currentUser); 
                }
                break;
            }
            case 3:
                // Back to Main Menu
                return;  // Exit the userMenu function
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}



int main() {
    std::vector<Bus> buses;
    std::vector<User> users; 
    Admin admin;
    User::loadUsersFromFile(users, "users.txt");
    // Load buses from file at the start
   
    admin.loadBusesFromFile(buses, "buses.txt");
    //loadFromFile(users, "users.txt");
    int choice;

    do {
        displayMainMenu();
        std::cout << "\n";
        getInput(choice, "Want to sign in as: ");
        

        switch (choice) {
            case 1:
                adminMenu(buses);
                break;
            case 2:
                userMenu(buses,users);
                break;
            case 3:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}