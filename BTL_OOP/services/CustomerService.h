#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <bits/stdc++.h>
#include "../models/Customer.h"
#include "../models/Ticket.h"

using namespace std;

class CustomerService {
private:
    vector<Customer> customers;
public:
    CustomerService();
    void addCustomerFromKeyboard();
    void updateCustomerFromKeyboard();
    void removeCustomerFromKeyboard();
    void addCustomer(const Customer& customer);
    void removeCustomer(const string& customerId);
    Customer getCustomerById(const string& customerId);
    void showAllCustomers();
    vector<Customer> getAllCustomers();
    void updateCustomer(const string& customerId, Customer& updatedCustomer);
    void loadCustomersFromFile(const string& filename);
    void saveCustomersToFile(const string& filename);
    void bookTicket(const string& customerId, const Ticket& ticket);
};

#endif //CUSTOMERSERVICE_H