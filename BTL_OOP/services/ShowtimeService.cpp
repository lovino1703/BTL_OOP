#include "ShowtimeService.h"
#include <bits/stdc++.h>

using namespace std;

ShowtimeService::ShowtimeService() {}

void ShowtimeService::addShowtime(const Time& time) {
    showtimes.push_back(time);
}

void ShowtimeService::removeShowtime(const string& timeId) {
    for (auto it = showtimes.begin(); it != showtimes.end(); ++it) {
        if (it->getId() == timeId) {
            showtimes.erase(it);
            cout << "Showtime with ID " << timeId << " removed successfully." << endl;
            return;
        }
    }
    cout << "Showtime with ID " << timeId << " not found." << endl;
}

vector<Time> ShowtimeService::getAllShowtimes() {
    return showtimes;
}

void ShowtimeService::updateShowtime(const string& timeId, Time& newTime) {
    for (auto& time : showtimes) {
        if (time.getId() == timeId) {
            time.setStartTime(newTime.getStartTime());
            cout << "Showtime with ID " << timeId << " updated successfully." << endl;
            return;
        }
    }
    cout << "Showtime with ID " << timeId << " not found." << endl;
}
