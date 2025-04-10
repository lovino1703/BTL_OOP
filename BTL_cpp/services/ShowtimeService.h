//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_SHOWTIMESERVICE_H
#define BTLPHUC_SHOWTIMESERVICE_H
#include <bits/stdc++.h>
#include "../models/Time.h"

class ShowtimeService {
private:
    std::vector<Time> showtimes;
public:
    ShowtimeService();
    void addShowtime(const Time& time);
    void removeShowtime(const std::string& timeId);
    std::vector<Time> getAllShowtimes();
    void updateShowtime(const std::string& timeId, Time& newTime);
};


#endif //BTLPHUC_SHOWTIMESERVICE_H
