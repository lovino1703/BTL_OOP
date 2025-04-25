//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_TIME_H
#define BTLPHUC_TIME_H
#include<bits/stdc++.h>

using namespace std;

class Time {
private:
    string id;
    string startTime;

public:
    Time();
    Time(string id, string startTime);

    string getId();
    string getStartTime();

    void setId(const string& newId);
    void setStartTime(const string& newStartTime);
};

#endif //BTLPHUC_TIME_H