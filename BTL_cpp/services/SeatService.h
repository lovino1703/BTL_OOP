//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_SEATSERVICE_H
#define BTLPHUC_SEATSERVICE_H
#include <bits/stdc++.h>
#include "../models/Seat.h"

using namespace std;

class SeatService {
private:
    vector<Seat> seats;
public:
    SeatService();
    void addSeat(const Seat& seat);
    void reserveSeat(const string& seatId);
    void cancelReservation(const string& seatId);
    vector<Seat> getAllSeats();
    void loadSeatsFromFile(const string& filename);
    void saveSeatsToFile(const string& filename);
    void addSeatFromKeyboard();
    void removeSeatFromKeyboard();
    void showAllSeats();
    void resetSeats();
};

#endif //BTLPHUC_SEATSERVICE_H