#include "admin.h"
#include "ErrorHandlers.h"
#include <fstream>
#include<iomanip>
#include <sstream>
#include<map>
#include <iostream>
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define BORDER GREEN
#define TEXT BLUE
#define BULLET BLUE
Admin admin;
 std::map<int, std::pair<std::string, std::string>>& Admin::getRouteMap()  {
    return routeMap;
}

void Admin::loadRoutesFromFile(const std::string &filename,  std::map<int, std::pair<std::string, std::string>> &routeMap) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open " << filename << "\n";
        return;
    }
    
    routeMap.clear(); // Clear any existing routes
    int index;
    std::string source, destination;
    
    while (infile >> index >> source >> destination) {
        routeMap[index] = {source, destination};
    }
    infile.close();
}

// Save all routes in the provided routeMap to a file (overwrites existing data in file)
void Admin::saveRoutesToFile(const std::string &filename,  std::map<int, std::pair<std::string, std::string>> &routeMap) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }

    for ( auto &route : routeMap) {
        outfile << route.first << " " << route.second.first << " " << route.second.second << "\n";
    }
    outfile.close();
}
void Admin::deleteRoute(int index, std::map<int, std::pair<std::string, std::string>> &routeMap, const std::string &filename) {
    auto it = routeMap.find(index);
    if (it != routeMap.end()) {
        routeMap.erase(it);  // Remove the route from the map
        saveRoutesToFile(filename, routeMap);  // Save the updated map to the file
        std::cout << "Route with index " << index << " deleted successfully.\n";
    } else {
        std::cerr << "Error: Route with index " << index << " not found.\n";
    }
}

// Add a new route to the routeMap and save to file
void Admin::addRoute(int index, const std::string &source, const std::string &destination,
                     std::map<int, std::pair<std::string, std::string>> &routeMap, const std::string &filename) {
    routeMap[index] = {source, destination};
    saveRoutesToFile(filename, routeMap); // Save updated map to file
}

// Function to load buses from file
void Admin::saveToPlan(const std::string& busName, int rows, int spaces, int seatsPerColumn, const std::string& filename) {
    // Open the specified file in append mode
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }

    // Write the bus layout details to the file
    file << busName << " " << rows << " " << spaces << " " << seatsPerColumn << "\n";
    file.close();

    std::cout << "Bus layout saved successfully to " << filename << "." << std::endl;
}
bool Admin::getSeatLayout(const std::string& busName, int& rows, int& spaces, int& seatsPerColumn) {
    std::ifstream file("plan.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open plan.txt" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        if (iss >> name >> rows >> spaces >> seatsPerColumn) {
            if (name == busName) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    std::cerr << "Error: No layout found for bus " << busName << std::endl;
    return false;
}
void Admin::loadBusesFromFile(std::vector<Bus>& buses, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Unable to open file for reading: " << filename << "\n";
        return;
    }
    buses.clear();  // Clear the vector to avoid duplicate entries

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string busName, route, daysOfOperation, startingTripPlace, endingTripPlace;
        int totalSeats;
        double distance, estimatedTravelTime;

        // Parse each field from the line
        std::getline(ss, busName, ',');
        std::getline(ss, route, ',');
        std::getline(ss, daysOfOperation, ',');
        std::getline(ss, startingTripPlace, ',');
        std::getline(ss, endingTripPlace, ',');
        ss >> totalSeats;
        ss.ignore(1, ',');  // Ignore the comma
        ss >> distance;
        ss.ignore(1, ',');  // Ignore the comma
        ss >> estimatedTravelTime;

        // Add the parsed bus to the vector
        buses.emplace_back(busName, totalSeats, route, daysOfOperation, distance, estimatedTravelTime, startingTripPlace, endingTripPlace);
    }
    file.close();
}
//-----------------new--------------------------------------------//


// Function to save buses to file
void Admin::saveBusesToFile(const std::vector<Bus>& buses, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Unable to open file for writing: " << filename << "\n";
        return;
    }

    for (const auto& bus : buses) {
        file << bus.getBusName() << ","
             << bus.getRoute() << ","
             << bus.getDaysOfOperation() << ","
             << bus.getStartingTripPlace() << ","
             << bus.getEndingTripPlace() << ","
             << bus.getTotalSeats() << ","
             << bus.getDistance() << ","
             << bus.getEstimatedTravelTime() << "\n";
    }
    file.close();
}
void Admin::adminLogin(std::vector<Bus>& buses) {
    std::string enteredUsername, enteredPassword;
    std::cout << "Enter Admin Username: ";
    std::cin >> enteredUsername;
    std::cout << "Enter Admin Password: ";
    std::cin >> enteredPassword;
    if (enteredUsername == adminUsername && enteredPassword == adminPassword) {
        std::cout << "Login successful!\n";
        manageBusDetails(buses);  // Call the existing admin menu function
    } else {
        std::cout << "Incorrect username or password. Access denied.\n";
    }
}
void Admin::manageBusDetails(std::vector<Bus>& buses) {
    int choice;
    do {

     int width = 50;
     std::string borderLine(width, '*');
    
    std::cout << "\n\n\n"; // Add vertical padding for centering
    std::cout << BORDER << "********************************************************************************\n" << RESET;
    std::cout << BORDER << "*" << RESET << "                                 " << BOLD << TEXT << "Management Portal" << RESET << "                                  " << BORDER << "*\n";
    std::cout << BORDER << "********************************************************************************\n" << RESET;

    std::cout << BORDER << borderLine << RESET << "\n";
    std::cout << BORDER << "*" << std::setw(width - 1) << "*\n" << RESET;
    
    std::cout << BORDER << "*" << BOLD << TEXT << " Manage Bus Details" << RESET 
              << std::setw(width - 18) << BORDER << "*" << RESET << "\n";
    std::cout << BORDER << borderLine << RESET << "\n";
    std::cout << BORDER << "*" << std::setw(width - 1) << "*" << RESET << "\n";
    
    // Simplified menu items
    std::cout << BORDER << "*" << RESET << BULLET << "  1. " << TEXT << "Add a new bus" << RESET 
              << std::setw(width - 17) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  2. " << TEXT << "Update bus information" << RESET 
              << std::setw(width - 23) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  3. " << TEXT << "Delete a bus" << RESET 
              << std::setw(width - 16) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  4. " << TEXT << "View all buses" << RESET 
              << std::setw(width - 18) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  5. " << TEXT << "Display Seat plan" << RESET 
              << std::setw(width - 22) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  6. " << TEXT << "Add Route" << RESET 
              << std::setw(width - 14) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  7. " << TEXT << "Delete Route" << RESET 
              << std::setw(width - 17) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << RESET << BULLET << "  8. " << TEXT << "Back to Admin Menu" << RESET 
              << std::setw(width - 24) << BORDER << "*" << RESET << "\n";

    std::cout << BORDER << "*" << std::setw(width - 1) << "*" << RESET << "\n";
    std::cout << BORDER << borderLine << RESET << "\n\n";

    int choice;
    admin.loadRoutesFromFile("routes.txt", admin.getRouteMap());
    getInput(choice, "Enter your choice: ");
        switch (choice) {
            case 1:
                addBus(buses);
                break;
            case 2:
                updateBus(buses);
                break;
            case 3:
                deleteBus(buses);
                break;
            case 4:
                displayAllBuses(buses);
                break;
            case 5:
                // Exit manage bus details menu
           
                displaySeatPattern(buses); 
                break;
            case 6:{
                admin.loadRoutesFromFile("routes.txt", admin.getRouteMap());
                // admin.loadRoutesFromFile("routes.txt", routeMap);
                 std::string startingTripPlace, endingTripPlace;
                 int routeIndex;
                 std::cout << "Enter Route No \n";
                 std::cin >> routeIndex;
                 std::cout << "Enter Starting Trip Place: ";
                 std::cin >> startingTripPlace;
                 std::cout << "Enter Ending Trip Place: ";
                 std::cin >> endingTripPlace;
                // auto& routeMap = admin.getRouteMap(); 
                 admin.addRoute(routeIndex, startingTripPlace, endingTripPlace,admin.getRouteMap(), "routes.txt");
                 break;
            }
            case 7:{
               //  admin.loadRoutesFromFile("routes.txt", routeMap);
                  admin.loadRoutesFromFile("routes.txt", admin.getRouteMap());
                 int routeIndex;
                 std::cout << "Enter Route No to delete \n";
                 std::cin >> routeIndex;
                 admin.deleteRoute(routeIndex, admin.getRouteMap(), "routes.txt");
                 break ;
            }
            case 8:
                 return ;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);
}
void Admin::addBus(std::vector<Bus>& buses) {
  std::string busName, route, daysOfOperation, startingTripPlace, endingTripPlace;
    int totalSeats, ID;
    double distance, estimatedTravelTime;
    int rows, seatsPerColumn, spaces;

    // Create an instance of Admin to access route map
    Admin admin;

    getInput(busName, "Enter Bus Name: ");
    getInput(totalSeats, "Enter Total Seats: ");
    admin.loadRoutesFromFile("routes.txt", admin.getRouteMap());
    // Enter routes
    getInput(ID, "Enter the Route ID (0 for custom route): ");
    if (ID == 0) {
        getInput(startingTripPlace, "Enter Starting Trip Place: ");
        getInput(endingTripPlace, "Enter Ending Trip Place: ");
    } else {
        auto it = admin.getRouteMap().find(ID);
        if (it != admin.getRouteMap().end()) {
            // Route found; set the starting and ending places
            startingTripPlace = it->second.first;
            endingTripPlace = it->second.second;
            std::cout << "Route found. Starting Trip Place: " << startingTripPlace 
                      << ", Ending Trip Place: " << endingTripPlace << "\n";
        } else {
            // Route not found
            std::cout << "No route found with ID " << ID << ".\n";
        }
    }

    getInput(daysOfOperation, "Enter Days of Operation: ");
    getInput(distance, "Enter Distance (in km): ");
    getInput(estimatedTravelTime, "Enter Estimated Travel Time (in hours): ");
    
    getInput(rows, "Enter Pattern Rows: ");
    getInput(seatsPerColumn, "Enter Pattern Columns: ");
    getInput(spaces, "Enter Pattern Spaces: ");

    admin.saveToPlan(busName, rows, spaces, seatsPerColumn, "plan.txt");
    route = startingTripPlace + " to " + endingTripPlace;
    buses.push_back(Bus(busName, totalSeats, route, daysOfOperation, distance, estimatedTravelTime,startingTripPlace,endingTripPlace));
    std::cout << "Bus added successfully!\n";
   // admin.saveBusesToFile(buses, "buses.txt");
    admin.saveBusesToFile(buses, "buses.txt");
}
void Admin::updateBus(std::vector<Bus>& buses) {
    int busIndex;
    std::cout << "Enter the index of the bus to update: ";
    std::cin >> busIndex;
    if (busIndex >= 1 && busIndex <= buses.size()) {
        // Prompt for updated information
        std::string busName, route, daysOfOperation,startingTripPlace, endingTripPlace;
        int totalSeats;
        double distance, estimatedTravelTime;
        int rows, seatsPerColumn, spaces;
        getInput(busName, "Enter updated Bus Name: ");
        getInput(totalSeats, "Enter updated Total Seats: ");
        getInput(rows, "Enter Pattern Rows: ");
        getInput(seatsPerColumn, "Enter Pattern Columns: ");
        getInput(spaces, "Enter Pattern Spaces: ");
        getInput(startingTripPlace, "Enter Starting Trip Place: ");
        getInput(endingTripPlace, "Enter Ending Trip Place: ");
        getInput(daysOfOperation, "Enter updated Days of Operation: ");
        getInput(distance, "Enter updated Distance (in km): ");
        getInput(estimatedTravelTime, "Enter updated Estimated Travel Time (in hours): ");
        // Update bus information
        admin.saveToPlan(busName, rows, spaces, seatsPerColumn, "plan.txt");
        buses[busIndex - 1] = Bus(busName, totalSeats, route, daysOfOperation, distance, estimatedTravelTime,startingTripPlace,  endingTripPlace);
        std::cout << "Bus updated successfully!\n";
        admin.saveBusesToFile(buses, "buses.txt");
    } else {
        std::cout << "Invalid bus index. No bus updated.\n";
    }
}
void Admin::deleteBus(std::vector<Bus>& buses) {
      std::string busName;
      std::cout << "Enter the Name of the bus: ";
      std::cin >> busName;
      int busIndex=-1;
      for (size_t i = 0; i < buses.size(); ++i) {
      if(buses[i].getBusName()==busName){
            busIndex=i+1;
            break;
                   }         
        }
    if (busIndex >= 1 && busIndex <= buses.size()) {
        // Erase the bus at the specified index
        buses.erase(buses.begin() + busIndex - 1);
        std::cout << "Bus deleted successfully!\n";
        admin.saveBusesToFile(buses, "buses.txt");
    } else {
        std::cout << "Invalid bus index. No bus deleted.\n";
    }
}

void Admin::displayAllBuses(const std::vector<Bus>& buses) {
    std::cout << "\nAll Buses:\n";
    std::string baseUrl = "https://www.mapdevelopers.com/distance_from_to.php?&from=";
    for (size_t i = 0; i < buses.size(); ++i) {
        const Bus& currentBus = buses[i];
        std::string url = baseUrl + currentBus.getStartingTripPlace() + "&to=" + currentBus.getEndingTripPlace();
        std::string distanceLink =url; 
        std::cout << "Bus " << i + 1 << " - " << currentBus.getBusName() << "\n";
        std::cout << "   Route: " << currentBus.getRoute() << "\n";
        std::cout << "   Source: " << currentBus.getStartingTripPlace() << "\n";
        std::cout << "   Destination: " << currentBus.getEndingTripPlace() << "\n";
        std::cout << "   Days of Operation: " << currentBus.getDaysOfOperation() << "\n";
        std::cout << "   Total Seats: " << currentBus.getTotalSeats() << "\n";
        std::cout << "   Current Occupancy: " << currentBus.getCurrentOccupancy() << "\n";
        std::cout << "   Available Seats: " << currentBus.getTotalSeats() - currentBus.getCurrentOccupancy() << "\n";
        std::cout << "   Distance: " << currentBus.getDistance() << " km\n";
        std::cout << "   Estimated Travel Time: " << currentBus.getEstimatedTravelTime() << " hours\n";
        std::cout << "   Distance Link: " << distanceLink << "\n";  // Display clickable link
        std::cout << "\n";
    }
}
void Admin::displaySeatPattern(const std::vector<Bus>& buses) {
std::string busName;
    std::cout << "Enter the bus name: ";
    std::cin >> busName;

    int rows, seatsPerColumn, spaces;
    if (!getSeatLayout(busName, rows, spaces, seatsPerColumn)) {
        return; // Exit if layout not found
    }

    // Find the specified bus in the provided list of buses
    const Bus* targetBus = nullptr;
    for (const auto& bus : buses) {
        if (bus.getBusName() == busName) {
            targetBus = &bus;
            break;
        }
    }

    if (targetBus == nullptr) {
        std::cerr << "Error: Bus " << busName << " not found in the list." << std::endl;
        return;
    }

    const std::vector<Seat>& seats = targetBus->getSeats();
    int seatNumber = 1;
    int totalSeats = targetBus->getTotalSeats();

    std::cout << "**************\n";
    for (int row = 0; row < rows; ++row) {
        for (int space = 0; space < spaces; ++space) {
            for (int col = 0; col < seatsPerColumn; ++col) {
                // Check if within total seat count and print with color coding
                if (seatNumber <= totalSeats) {
                    const Seat& seat = seats[seatNumber - 1];
                    if (seat.isSeatBooked()) {
                        std::cout << "\033[31m"; // Red for booked
                    } else {
                        std::cout << "\033[32m"; // Green for available
                    }
                    std::cout << std::setw(2) << seatNumber << " ";
                    std::cout << "\033[0m"; // Reset color
                    ++seatNumber;
                } else {
                    std::cout << "   "; // Blank space if no seat available
                }
            }
            std::cout << "   "; // Spaces between columns
        }
        std::cout << std::string(spaces, ' ') << std::endl;
    }
    std::cout << "*************\n";
}
// void Admin::displaySeatPattern(const std::vector<Bus>& buses)  {
//     int index;
//     int rows,seatsPerColumn,spaces;
//     std::cout<<"Index of the Bus ";
//     std::cin>>index;
//     std::cout<<"Patter rows ";
//     std::cin>>rows;
//     std::cout<<"Patter coloumn ";
//     std::cin>>seatsPerColumn;
//     std::cout<<"Patter spaces ";
//     std::cin>>spaces;
//     int seatNumber = 1;
//     const Bus& currentBus = buses[index-1];
//     int totalSeats=currentBus.getTotalSeats();
//     std::cout<<"Total Seats are\n";
//     std::cout<<totalSeats;
//     std::cout << "\n";
//     if (rows * seatsPerColumn > totalSeats) {
//         std::cout << "Error: Not enough seats to generate this pattern." << std::endl;
//         return;
//     }
//     std::cout<<"*************************************************************\n";
//     for (int row = 0; row < rows; ++row) {
//         for(int space=0;space<spaces;space++){
//         for (int col = 0; col < seatsPerColumn; ++col) {
//             // Print seat number if it's within the total seat count
//             if (seatNumber <= totalSeats) {
//                 std::cout << std::setw(2) << seatNumber<<"*";
//                 ++seatNumber;
//             } else {
//                 std::cout << "   "; // Blank space if no seat available
//             }
//         }
//           std::cout << "   "; 
//         }
//         // Print spaces between columns
//         std::cout << std::string(spaces, ' ');
//         std::cout << std::endl;
//     }
//     std::cout<<"*************************************************************\n";
// }