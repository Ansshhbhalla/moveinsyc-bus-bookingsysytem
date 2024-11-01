#include "bus.h"

Bus::Bus(const std::string& name, int seats, const std::string& route, const std::string& days,
        double distance, double estimatedTime ,const std::string& startingTripPlace, const std::string& endingTripPlace)
    : busName(name), totalSeats(seats), currentOccupancy(0), route(route), daysOfOperation(days),
      distance(distance), estimatedTravelTime(estimatedTime) , startingTripPlace(startingTripPlace) ,endingTripPlace(endingTripPlace) {
    // Initialize seats
    for (int i = 1; i <= totalSeats; ++i) {
        Seat seat(i);
        this->seats.push_back(seat);
    }
}

double Bus::getDistance() const {
    return distance;
}

double Bus::getEstimatedTravelTime() const {
    return estimatedTravelTime;
}

const std::string& Bus::getBusName() const {
    return busName;
}
const std::string& Bus::getStartingTripPlace() const {
    return startingTripPlace;
}
const std::string& Bus:: getEndingTripPlace() const {
    return endingTripPlace;
}
int Bus::getTotalSeats() const {
    return totalSeats;
}

int Bus::getCurrentOccupancy() const {
    return currentOccupancy;
}

const std::string& Bus::getRoute() const {
    return route;
}

const std::string& Bus::getDaysOfOperation() const {
    return daysOfOperation;
}

const std::vector<Seat>& Bus::getSeats() const {
    return seats;
}

bool Bus::bookSeat(int seatNumber) {
    if (seatNumber >= 1 && seatNumber <= totalSeats && !seats[seatNumber - 1].isSeatBooked()) {
        seats[seatNumber - 1].bookSeat();
        ++currentOccupancy;
        return true;
    }
    return false;
}

bool Bus::cancelSeatBooking(int seatNumber) {
    if (seatNumber >= 1 && seatNumber <= totalSeats && seats[seatNumber - 1].isSeatBooked()) {
        seats[seatNumber - 1].cancelBooking();
        --currentOccupancy;
        return true;
    }
    return false;
}
