//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_SEATSERVICE_H
#define BTLPHUC_SEATSERVICE_H
#include <bits/stdc++.h>
#include "../models/Seat.h"

class SeatService {
private:
    std::vector<Seat> seats;
public:
    SeatService();
    void addSeat(const Seat& seat);
    void reserveSeat(const std::string& seatId);
    void cancelReservation(const std::string& seatId);
    std::vector<Seat> getAllSeats();
    void loadSeatsFromFile(const std::string& filename);
    void saveSeatsToFile(const std::string& filename);
    void addSeatFromKeyboard();
    void removeSeatFromKeyboard();
    void showAllSeats();
    void resetSeats();

};


#endif //BTLPHUC_SEATSERVICE_H
