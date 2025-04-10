// Ticket.cpp
#include "Ticket.h"
#include <ctime>

std::string getCurrentDate() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

Ticket::Ticket(std::string id, double price, Seat seat)
        : id(id), price(price), seat(seat) {
    this->bookingDate = getCurrentDate();
}

Ticket::Ticket(std::string id, double price, Seat seat, std::string movieId,
               std::string showtimeId, std::string customerId)
        : id(id), price(price), seat(seat), movieId(movieId),
          showtimeId(showtimeId), customerId(customerId) {
    this->bookingDate = getCurrentDate();
}

// Các phương thức getter và setter
std::string Ticket::getId() const {
    return id;
}

double Ticket::getPrice() const {
    return price;
}

Seat Ticket::getSeat() const {
    return seat;
}

std::string Ticket::getMovieId() const {
    return movieId;
}

std::string Ticket::getShowtimeId() const {
    return showtimeId;
}

std::string Ticket::getCustomerId() const {
    return customerId;
}

std::string Ticket::getBookingDate() const {
    return bookingDate;
}

void Ticket::setMovieId(std::string movieId) {
    this->movieId = movieId;
}

void Ticket::setShowtimeId(std::string showtimeId) {
    this->showtimeId = showtimeId;
}

void Ticket::setCustomerId(std::string customerId) {
    this->customerId = customerId;
}

void Ticket::setBookingDate(std::string bookingDate) {
    this->bookingDate = bookingDate;
}
