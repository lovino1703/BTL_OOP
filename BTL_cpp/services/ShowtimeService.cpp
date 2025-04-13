//
// Created by admin on 4/24/2025.
//

#include "ShowtimeService.h"
#include <bits/stdc++.h>

ShowtimeService::ShowtimeService() {}

void ShowtimeService::addShowtime(const Time& time) {
    showtimes.push_back(time);
}

void ShowtimeService::removeShowtime(const std::string& timeId) {
    for (auto it = showtimes.begin(); it != showtimes.end(); ++it) {
        if (it->getId() == timeId) {
            showtimes.erase(it);
            std::cout << "Showtime with ID " << timeId << " removed successfully." << std::endl;
            return;
        }
    }
    std::cout << "Showtime with ID " << timeId << " not found." << std::endl;

}

std::vector<Time> ShowtimeService::getAllShowtimes() {
    return showtimes;
}

void ShowtimeService::updateShowtime(const std::string& timeId,Time& newTime) {
    for (auto& time : showtimes) {
        if (time.getId() == timeId) {
            time.setStartTime(newTime.getStartTime());
            std::cout << "Showtime with ID " << timeId << " updated successfully." << std::endl;
            return;
        }
    }
    std::cout << "Showtime with ID " << timeId << " not found." << std::endl;
}