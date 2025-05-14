#include "Customer.h"
#include <bits/stdc++.h>

using namespace std;

Customer::Customer() : id(""), name(""), phone(""), email("") {}

Customer::Customer(string id, string name, string phone, string email, vector<Ticket> tickets)
    : id(id), name(name), phone(phone), email(email), tickets(tickets) {}

string Customer::getId() {
    return id;
}

string Customer::getName() {
    return name;
}

string Customer::getPhone() {
    return phone;
}

string Customer::getEmail() {
    return email;
}

vector<Ticket> Customer::getTickets() {
    return tickets;
}

void Customer::setId(const string& newId) {
    id = newId;
}

void Customer::setName(const string& newName) {
    name = newName;
}

void Customer::setPhone(const string& newPhone) {
    phone = newPhone;
}

void Customer::setEmail(const string& newEmail) {
    email = newEmail;
}

void Customer::setTickets(const vector<Ticket>& newTickets) {
    tickets = newTickets;
}

void Customer::addTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
}