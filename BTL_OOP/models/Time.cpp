#include "Time.h"
#include <bits/stdc++.h>

using namespace std;

Time::Time() : id(""), startTime("") {}

Time::Time(string id, string startTime) : id(id), startTime(startTime) {}

string Time::getId() {
    return id;
}

string Time::getStartTime() {
    return startTime;
}

void Time::setId(const string& newId) {
    id = newId;
}

void Time::setStartTime(const string& newStartTime) {
    startTime = newStartTime;
}