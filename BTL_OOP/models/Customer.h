#ifndef CUSTOMER_H
#define CUSTOMER_H

#include<bits/stdc++.h>
#include "../models/Ticket.h"

using namespace std;

class Customer {
private:
    string id;
    string name;
    string phone;
    string email;
    vector<Ticket> tickets;

public:
    Customer();
    Customer(string id, string name, string phone, string email, vector<Ticket> tickets = {});
    string getId();
    string getName();
    string getPhone();
    string getEmail();
    vector<Ticket> getTickets();

    void setId(const string& newId);
    void setName(const string& newName);
    void setPhone(const string& newPhone);
    void setEmail(const string& newEmail);
    void setTickets(const vector<Ticket>& newTickets);

    void addTicket(const Ticket& ticket);
};

#endif //CUSTOMER_H