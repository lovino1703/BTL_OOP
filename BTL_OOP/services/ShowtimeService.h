#ifndef SHOWTIMESERVICE_H
#define SHOWTIMESERVICE_H
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


#endif //SHOWTIMESERVICE_H
