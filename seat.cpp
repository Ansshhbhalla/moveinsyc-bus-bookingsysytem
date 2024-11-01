#include "seat.h"

Seat::Seat(int number) : seatNumber(number), isBooked(false) {}

int Seat::getSeatNumber() const {
    return seatNumber;
}

bool Seat::isSeatBooked() const {
    return isBooked;
}

void Seat::bookSeat() {
    isBooked = true;
}

void Seat::cancelBooking() {
    isBooked = false;
}
