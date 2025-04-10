//
// Created by admin on 4/24/2025.
//

#include "Time.h"
#include <bits/stdc++.h>

Time::Time() : id(""), startTime("") {}

Time::Time(std::string id, std::string startTime) : id(id), startTime(startTime) {}

std::string Time::getId() {
    return id;
}

std::string Time::getStartTime() {
    return startTime;
}

void Time::setId(const std::string& newId) {
    id = newId;
}

void Time::setStartTime(const std::string& newStartTime) {
    startTime = newStartTime;
}


