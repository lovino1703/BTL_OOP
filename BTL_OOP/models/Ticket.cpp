#include "Ticket.h"
#include <ctime>

using namespace std;

string getCurrentDate() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}

Ticket::Ticket(string id, double price, Seat seat)
    : id(id), price(price), seat(seat) {
    this->bookingDate = getCurrentDate();
}

Ticket::Ticket(string id, double price, Seat seat, string movieId,
               string showtimeId, string customerId)
    : id(id), price(price), seat(seat), movieId(movieId),
      showtimeId(showtimeId), customerId(customerId) {
    this->bookingDate = getCurrentDate();
}

// Getter methods
string Ticket::getId() const {
    return id;
}

double Ticket::getPrice() const {
    return price;
}

Seat Ticket::getSeat() const {
    return seat;
}

string Ticket::getMovieId() const {
    return movieId;
}

string Ticket::getShowtimeId() const {
    return showtimeId;
}

string Ticket::getCustomerId() const {
    return customerId;
}

string Ticket::getBookingDate() const {
    return bookingDate;
}

// Setter methods
void Ticket::setMovieId(string movieId) {
    this->movieId = movieId;
}

void Ticket::setShowtimeId(string showtimeId) {
    this->showtimeId = showtimeId;
}

void Ticket::setCustomerId(string customerId) {
    this->customerId = customerId;
}

void Ticket::setBookingDate(string bookingDate) {
    this->bookingDate = bookingDate;
}