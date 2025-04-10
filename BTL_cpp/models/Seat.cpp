// Seat.cpp
#include "Seat.h"

Seat::Seat() : isAvailable(true) {}

Seat::Seat(std::string movieId, std::string id, std::string showtimeId, bool isAvailable)
        : movieId(movieId), id(id), showtimeId(showtimeId), isAvailable(isAvailable) {}

std::string Seat::getId() const {
    return id;
}

std::string Seat::getMovieId() const {
    return movieId;
}

std::string Seat::getShowtimeId() const {
    return showtimeId;
}

bool Seat::getIsAvailable() const {
    return isAvailable;
}

void Seat::setId(std::string id) {
    this->id = id;
}

void Seat::setMovieId(std::string movieId) {
    this->movieId = movieId;
}

void Seat::setShowtimeId(std::string showtimeId) {
    this->showtimeId = showtimeId;
}

void Seat::setIsAvailable(bool isAvailable) {
    this->isAvailable = isAvailable;
}
