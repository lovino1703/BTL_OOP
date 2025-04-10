//
// Created by admin on 4/24/2025.
//

#include "Customer.h"
#include<bits/stdc++.h>

Customer::Customer() : id(""), name(""), phone(""), email("") {}

Customer::Customer(std::string id, std::string name, std::string phone, std::string email, std::vector<Ticket> tickets)
        : id(id), name(name), phone(phone), email(email), tickets(tickets) {}

std::string Customer::getId() {
    return id;
}

std::string Customer::getName() {
    return name;
}

std::string Customer::getPhone() {
    return phone;
}

std::string Customer::getEmail() {
    return email;
}

std::vector<Ticket> Customer::getTickets() {
    return tickets;
}

void Customer::setId(const std::string& newId) {
    id = newId;
}

void Customer::setName(const std::string& newName) {
    name = newName;
}

void Customer::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

void Customer::setEmail(const std::string& newEmail) {
    email = newEmail;
}

void Customer::setTickets(const std::vector<Ticket>& newTickets) {
    tickets = newTickets;
}

void Customer::addTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
}