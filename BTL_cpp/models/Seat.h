// Seat.h
#ifndef BTLPHUC_SEAT_H
#define BTLPHUC_SEAT_H

#include <string>

class Seat {
private:
    std::string id;
    std::string movieId;
    std::string showtimeId;
    bool isAvailable;

public:
    Seat();
    Seat(std::string movieId, std::string id, std::string showtimeId, bool isAvailable);

    std::string getId() const;
    std::string getMovieId() const;
    std::string getShowtimeId() const;
    bool getIsAvailable() const;

    void setId(std::string id);
    void setMovieId(std::string movieId);
    void setShowtimeId(std::string showtimeId);
    void setIsAvailable(bool isAvailable);
};

#endif //BTLPHUC_SEAT_H
