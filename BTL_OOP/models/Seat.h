#ifndef SEAT_H
#define SEAT_H

#include <string>

using namespace std;

class Seat {
private:
    string id;
    string movieId;
    string showtimeId;
    bool isAvailable;

public:
    Seat();
    Seat(string movieId, string id, string showtimeId, bool isAvailable);

    string getId() const;
    string getMovieId() const;
    string getShowtimeId() const;
    bool getIsAvailable() const;

    void setId(string id);
    void setMovieId(string movieId);
    void setShowtimeId(string showtimeId);
    void setIsAvailable(bool isAvailable);
};

#endif //SEAT_H