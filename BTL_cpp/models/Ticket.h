// Ticket.h
#ifndef BTLPHUC_TICKET_H
#define BTLPHUC_TICKET_H

#include <string>
#include "../models/Seat.h"
#include "../models/Movie.h"

class Ticket {
private:
    std::string id;
    double price;
    Seat seat;
    std::string movieId;
    std::string showtimeId;
    std::string customerId;
    std::string bookingDate;

public:
    Ticket(){};
    Ticket(std::string id, double price, Seat seat);
    Ticket(std::string id, double price, Seat seat, std::string movieId,
           std::string showtimeId, std::string customerId);

    std::string getId() const;
    double getPrice() const;
    Seat getSeat() const;
    std::string getMovieId() const;
    std::string getShowtimeId() const;
    std::string getCustomerId() const;
    std::string getBookingDate() const;

    void setMovieId(std::string movieId);
    void setShowtimeId(std::string showtimeId);
    void setCustomerId(std::string customerId);
    void setBookingDate(std::string bookingDate);
};

#endif //BTLPHUC_TICKET_H
