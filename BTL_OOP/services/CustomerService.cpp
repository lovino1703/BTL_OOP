#include "CustomerService.h"
#include <bits/stdc++.h>
#include "../models/Customer.h"
#include "../models/Ticket.h"
#include "MovieService.h"
#include "../handle.h"

using namespace std;

CustomerService::CustomerService() {
    // Constructor implementation
}

void CustomerService::addCustomer(const Customer& customer) {
    customers.push_back(customer);
}

void CustomerService::removeCustomer(const string& customerId) {
    customers.erase(remove_if(customers.begin(), customers.end(),
                        [&customerId](Customer& customer) { return customer.getId() == customerId; }),
                     customers.end());
}

Customer CustomerService::getCustomerById(const string& customerId) {
    for (auto& customer : customers) {
        if (customer.getId() == customerId) {
            return customer;
        }
    }
    Customer customer;
    customer.setId("-1");
    throw runtime_error("Customer not found" + customerId);
    return customer;
}

vector<Customer> CustomerService::getAllCustomers() {
    return customers;
}

void CustomerService::updateCustomer(const string& customerId, Customer& updatedCustomer) {
    for (auto& customer : customers) {
        if (customer.getId() == customerId) {
            customer.setName(updatedCustomer.getName());
            customer.setPhone(updatedCustomer.getPhone());
            customer.setEmail(updatedCustomer.getEmail());
            customer.setTickets(updatedCustomer.getTickets());
            return;
        }
    }
    throw runtime_error("Customer not found");
}

void CustomerService::loadCustomersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            throw runtime_error("Khong the tao file: " + filename);
        }
        outFile.close();
        return;
    }

    customers.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string id, name, phone, email;

        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, phone, ',');
        getline(iss, email);

        Customer customer(id, name, phone, email, vector<Ticket>());

        string ticketFilename = "../data/tickets.txt";
        ifstream ticketFile(ticketFilename);

        if (ticketFile.is_open()) {
            string ticketLine;
            while (getline(ticketFile, ticketLine)) {
                if (ticketLine.empty()) continue;

                istringstream ticketIss(ticketLine);
                string ticketId, priceStr, movieId, seatId, showtimeId, customerId, bookingDate;

                getline(ticketIss, ticketId, ',');
                getline(ticketIss, priceStr, ',');
                getline(ticketIss, movieId, ',');
                getline(ticketIss, seatId, ',');
                getline(ticketIss, showtimeId, ',');
                getline(ticketIss, customerId, ',');
                getline(ticketIss, bookingDate);

                if(customerId == customer.getId()){
                    double price = stod(priceStr);
                    Seat seat(movieId, seatId, showtimeId, false);
                    Ticket ticket(ticketId, price, seat, movieId, showtimeId, customerId);
                    ticket.setBookingDate(bookingDate);
                    customer.addTicket(ticket);
                }
            }
            ticketFile.close();
        }

        customers.push_back(customer);
    }
    file.close();
}

void CustomerService::bookTicket(const string &customerId, const Ticket &ticket) {
   Customer customer = getCustomerById(customerId);
   customer.addTicket(ticket);
}

void CustomerService::saveCustomersToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Khong the mo file: " + filename);
    }

    for (auto& customer : customers) {
        file << customer.getId() << ","
             << customer.getName() << ","
             << customer.getPhone() << ","
             << customer.getEmail() << "\n";
    }
    file.close();
}

void CustomerService::showAllCustomers() {
    loadCustomersFromFile("../data/customer.txt");
    if (customers.empty()) {
        handle::handle_view_banner_empty_customer();
        return;
    }

    handle::handle_view_banner_list_customer();

    MovieService movieService;
    try {
        movieService.loadMoviesFromFile("../data/movie.txt");
    } catch (const runtime_error& e) {
        cerr << "Loi khi tai du lieu phim: " << e.what() << endl;
    }

    for (auto& customer : customers) {
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "| ID khach hang: " << left << setw(47) << customer.getId() << "|" << endl;
        cout << "|-----------------------------------------------------------|" << endl;
        cout << "| Ten:           " << left << setw(47) << customer.getName() << "|" << endl;
        cout << "| So dien thoai: " << left << setw(47) << customer.getPhone() << "|" << endl;
        cout << "| Email:         " << left << setw(47) << customer.getEmail() << "|" << endl;

        vector<Ticket> tickets = customer.getTickets();
        cout << "|-----------------------------------------------------------|" << endl;
        cout << "| So ve da dat:  " << left << setw(47) << tickets.size() << "|" << endl;

        if (!tickets.empty()) {
            cout << "|-----------------------------------------------------------|" << endl;
            cout << "| Danh sach ve:                                             |" << endl;

            for (auto& ticket : tickets) {
                cout << "| - Ma ve: " << left << setw(49) << ticket.getId() << "|" << endl;
                cout << "|   Gia:   " << left << setw(50) << ticket.getPrice() << "|" << endl;

                Seat seat = ticket.getSeat();
                cout << "| Ghe: " << left << setw(50) << seat.getId() << "|" << endl;
                try {
                    Movie movie = movieService.getMovieById(ticket.getMovieId());
                    cout << "|   Phim:  " << left << setw(50) << movie.getName() << "|" << endl;
                } catch (const runtime_error& e) {
                    cout << "|   Phim:  " << left << setw(50) << "Khong co thong tin" << "|" << endl;
                }

                if (ticket.getShowtimeId() != "") {
                    cout << "|   Suat:  " << left << setw(50) << ticket.getShowtimeId() << "|" << endl;
                }

                cout << "|-----------------------------------------------------------|" << endl;
            }
        }

        cout << "+-----------------------------------------------------------+" << endl;
        cout << endl;
    }

    cout << "====================== KET THUC ======================" << endl;
}

void CustomerService::addCustomerFromKeyboard() {
    string id, name, phone, email;

    handle::handle_view_banner_add_customer();

    cout << "| ID khach hang: ";
    cin >> id;

    cin.ignore();

    cout << "| Ten khach hang: ";
    getline(cin, name);

    cout << "| So dien thoai: ";
    getline(cin, phone);

    cout << "| Email: ";
    getline(cin, email);

    addCustomer(Customer(id, name, phone, email, vector<Ticket>()));
    try {
        saveCustomersToFile("../data/customer.txt");
    } catch (const exception& e) {
        cerr << "Error saving customer data: " << e.what() << endl;
    }
    handle::handle_view_alert_add_customer_success();
}

void CustomerService::updateCustomerFromKeyboard() {
    string customerId;

    handle::handle_view_banner_list_customer();
    for (auto& customer : customers) {
        cout << "ID: " << customer.getId() << ", Ten: " << customer.getName()
             << ", SDT: " << customer.getPhone() << ", Email: " << customer.getEmail() << endl;
    }

    handle::handle_view_banner_update_customer();

    cout << "| Nhap ID khach hang can cap nhat: ";
    cin >> customerId;

    bool found = false;
    Customer currentCustomer;

    try {
        currentCustomer = getCustomerById(customerId);
        found = true;
    } catch (const runtime_error& e) {
        cout << "| Khong tim thay khach hang voi ID: " << customerId << endl;
        cout << "+-----------------------------------------------------------+" << endl;
        return;
    }

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                THONG TIN KHACH HANG HIEN TAI              |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "| ID: " << currentCustomer.getId() << endl;
    cout << "| Ten: " << currentCustomer.getName() << endl;
    cout << "| SDT: " << currentCustomer.getPhone() << endl;
    cout << "| Email: " << currentCustomer.getEmail() << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    cin.ignore();

    cout << "|          NHAP THONG TIN MOI (DE TRONG DE GIU NGUYEN)      |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    string name, phone, email;

    cout << "| Ten khach hang: ";
    getline(cin, name);
    if (name.empty()) name = currentCustomer.getName();

    cout << "| So dien thoai: ";
    getline(cin, phone);
    if (phone.empty()) phone = currentCustomer.getPhone();

    cout << "| Email: ";
    getline(cin, email);
    if (email.empty()) email = currentCustomer.getEmail();

    Customer updatedCustomer(customerId, name, phone, email, currentCustomer.getTickets());

    try {
        updateCustomer(customerId, updatedCustomer);
        saveCustomersToFile("../data/customer.txt");
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "|              CAP NHAT KHACH HANG THANH CONG!              |" << endl;
        cout << "+-----------------------------------------------------------+" << endl;
    } catch (const runtime_error& e) {
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "| Loi: " << e.what() << endl;
        cout << "+-----------------------------------------------------------+" << endl;
    }
}

void CustomerService::removeCustomerFromKeyboard() {
    showAllCustomers();

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                    XOA KHACH HANG                         |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    string customerId;
    cout << "| Nhap ID khach hang can xoa: ";
    cin >> customerId;

    try {
        getCustomerById(customerId);
        removeCustomer(customerId);
        saveCustomersToFile("../data/customer.txt");
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "|               DA XOA KHACH HANG THANH CONG!               |" << endl;
        cout << "+-----------------------------------------------------------+" << endl;
    } catch (const runtime_error& e) {
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "| Loi: Khong tim thay khach hang voi ID: " << customerId << endl;
        cout << "+-----------------------------------------------------------+" << endl;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}