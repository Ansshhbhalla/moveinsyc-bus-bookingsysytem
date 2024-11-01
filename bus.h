#ifndef BUS_H
#define BUS_H


#include <iostream>
#include <vector>
#include <string>
#include "seat.h"

class Bus {
private:
    std::string busName;
    int totalSeats;
    int currentOccupancy;
    std::vector<Seat> seats;
    std::string route;
    std::string daysOfOperation;
    std::string startingTripPlace, endingTripPlace;
    double distance, estimatedTravelTime;

public:
    Bus(const std::string& name, int seats, const std::string& route, const std::string& days,
        double distance, double estimatedTime ,const std::string& startingTripPlace, const std::string& endingTripPlace);
    double getDistance() const;
    double getEstimatedTravelTime() const;
    const std::string& getBusName() const;
    int getTotalSeats() const;
    int getCurrentOccupancy() const;
    const std::string&  getRoute() const;
    const std::string&  getDaysOfOperation() const;
    const std::string&  getStartingTripPlace() const;
    const std::string&  getEndingTripPlace() const;
    const std::vector<Seat>& getSeats() const;
    bool bookSeat(int seatNumber);
    bool cancelSeatBooking(int seatNumber);
    void displaySeatPattern(int rows, int spaces, int seatsPerColumn) ;
    
};

#endif // BUS_H
