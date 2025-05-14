#ifndef SEATSERVICE_H
#define SEATSERVICE_H
#include <bits/stdc++.h>
#include "../models/Seat.h"

using namespace std;

class SeatService {
private:
    vector<Seat> seats;
public:
    SeatService();
    void addSeat(const Seat& seat);
    void reserveSeat(const string& seatId,const string& showtimes,const string& movieId);
    void cancelReservation(const string& seatId);
    vector<Seat> getAllSeats();
    void loadSeatsFromFile(const string& filename);
    void saveSeatsToFile(const string& filename);
    void addSeatFromKeyboard();
    void removeSeatFromKeyboard();
    void showAllSeats();
    void resetSeats();

};


#endif //SEATSERVICE_H
