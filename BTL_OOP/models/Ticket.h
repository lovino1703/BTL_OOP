#ifndef TICKET_H
#define TICKET_H

#include <string>
#include "../models/Seat.h"
#include "../models/Movie.h"

using namespace std;

class Ticket {
private:
    string id;
    double price;
    Seat seat;
    string movieId;
    string showtimeId;
    string customerId;
    string bookingDate;

public:
    Ticket(){};
    Ticket(string id, double price, Seat seat);
    Ticket(string id, double price, Seat seat, string movieId,
           string showtimeId, string customerId);

    string getId() const;
    double getPrice() const;
    Seat getSeat() const;
    string getMovieId() const;
    string getShowtimeId() const;
    string getCustomerId() const;
    string getBookingDate() const;

    void setMovieId(string movieId);
    void setShowtimeId(string showtimeId);
    void setCustomerId(string customerId);
    void setBookingDate(string bookingDate);
};

#endif //TICKET_H