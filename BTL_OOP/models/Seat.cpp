#include "Seat.h"

using namespace std;

Seat::Seat() : isAvailable(true) {}

Seat::Seat(string movieId, string id, string showtimeId, bool isAvailable)
    : movieId(movieId), id(id), showtimeId(showtimeId), isAvailable(isAvailable) {}

string Seat::getId() const {
    return id;
}

string Seat::getMovieId() const {
    return movieId;
}

string Seat::getShowtimeId() const {
    return showtimeId;
}

bool Seat::getIsAvailable() const {
    return isAvailable;
}

void Seat::setId(string id) {
    this->id = id;
}

void Seat::setMovieId(string movieId) {
    this->movieId = movieId;
}

void Seat::setShowtimeId(string showtimeId) {
    this->showtimeId = showtimeId;
}

void Seat::setIsAvailable(bool isAvailable) {
    this->isAvailable = isAvailable;
}