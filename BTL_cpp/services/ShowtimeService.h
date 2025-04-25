//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_SHOWTIMESERVICE_H
#define BTLPHUC_SHOWTIMESERVICE_H
#include <bits/stdc++.h>
#include "../models/Time.h"

using namespace std;

class ShowtimeService {
private:
    vector<Time> showtimes;
public:
    ShowtimeService();
    void addShowtime(const Time& time);
    void removeShowtime(const string& timeId);
    vector<Time> getAllShowtimes();
    void updateShowtime(const string& timeId, Time& newTime);
};

#endif //BTLPHUC_SHOWTIMESERVICE_H