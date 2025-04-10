//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_CUSTOMERSERVICE_H
#define BTLPHUC_CUSTOMERSERVICE_H

#include <bits/stdc++.h>
#include "../models/Customer.h"
#include "../models/Ticket.h"


class CustomerService {
private:
    std::vector<Customer> customers;
public:
    CustomerService();
    void addCustomerFromKeyboard();
    void updateCustomerFromKeyboard();
    void removeCustomerFromKeyboard();
    void addCustomer(const Customer& customer);
    void removeCustomer(const std::string& customerId);
    Customer getCustomerById(const std::string& customerId);
    void showAllCustomers();
    std::vector<Customer> getAllCustomers();
    void updateCustomer(const std::string& customerId, Customer& updatedCustomer);
    void loadCustomersFromFile(const std::string& filename);
    void saveCustomersToFile(const std::string& filename);
    void bookTicket(const std::string& customerId, const Ticket& ticket);
};


#endif //BTLPHUC_CUSTOMERSERVICE_H
