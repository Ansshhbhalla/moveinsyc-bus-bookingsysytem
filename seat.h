#ifndef SEAT_H
#define SEAT_H

class Seat {
private:
    int seatNumber;
    bool isBooked;

public:
    Seat(int number);

    int getSeatNumber() const;
    bool isSeatBooked() const;
    void bookSeat();
    void cancelBooking();
};

#endif // SEAT_H
