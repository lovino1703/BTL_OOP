//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_TIME_H
#define BTLPHUC_TIME_H
#include<bits/stdc++.h>

class Time {
private:
    std::string id;
    std::string startTime;

public:
    Time();
    Time(std::string id, std::string startTime);

    std::string getId();
    std::string getStartTime();

    void setId(const std::string& newId);
    void setStartTime(const std::string& newStartTime);

};


#endif //BTLPHUC_TIME_H
