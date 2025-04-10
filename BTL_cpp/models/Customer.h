//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_CUSTOMER_H
#define BTLPHUC_CUSTOMER_H
#include<bits/stdc++.h>
#include "../models/Ticket.h"


class Customer {
private:
    std::string id;
    std::string name;
    std::string phone;
    std::string email;
    std::vector<Ticket> tickets;

public:
    Customer();
    Customer(std::string id, std::string name, std::string phone, std::string email, std::vector<Ticket> tickets = {});
    std::string getId();
    std::string getName();
    std::string getPhone();
    std::string getEmail();
    std::vector<Ticket> getTickets();

    void setId(const std::string& newId);
    void setName(const std::string& newName);
    void setPhone(const std::string& newPhone);
    void setEmail(const std::string& newEmail);
    void setTickets(const std::vector<Ticket>& newTickets);

    void addTicket(const Ticket& ticket);

};


#endif //BTLPHUC_CUSTOMER_H
