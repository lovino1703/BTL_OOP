//
// Created by admin on 4/24/2025.
//

#include "CustomerService.h"
#include <bits/stdc++.h>
#include "../models/Customer.h"
#include "../models/Ticket.h"
#include "MovieService.h"
#include "../handle.h"


CustomerService::CustomerService() {
    // Constructor implementation
}

void CustomerService::addCustomer(const Customer& customer) {
    customers.push_back(customer);
}

void CustomerService::removeCustomer(const std::string& customerId) {
    customers.erase(std::remove_if(customers.begin(), customers.end(),
                                    [&customerId](Customer& customer) { return customer.getId() == customerId; }),
                     customers.end());
}

Customer CustomerService::getCustomerById(const std::string& customerId) {
    for (auto& customer : customers) {
        if (customer.getId() == customerId) {
            return customer;
        }
    }
    Customer customer;
    customer.setId("-1");
    throw std::runtime_error("Customer not found" + customerId);
    return customer;
}

std::vector<Customer> CustomerService::getAllCustomers() {
    return customers;
}

void CustomerService::updateCustomer(const std::string& customerId,Customer& updatedCustomer) {
    for (auto& customer : customers) {
        if (customer.getId() == customerId) {
            customer.setName(updatedCustomer.getName());
            customer.setPhone(updatedCustomer.getPhone());
            customer.setEmail(updatedCustomer.getEmail());
            customer.setTickets(updatedCustomer.getTickets());
            return;
        }
    }
    throw std::runtime_error("Customer not found");
}

void CustomerService::loadCustomersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Tao file neu chua ton tai
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            throw std::runtime_error("Khong the tao file: " + filename);
        }
        outFile.close();
        return;
    }

    customers.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string id, name, phone, email;

        std::getline(iss, id, ',');
        std::getline(iss, name, ',');
        std::getline(iss, phone, ',');
        std::getline(iss, email);

        // Tao doi tuong Customer voi vector ve rong
        Customer customer(id, name, phone, email, std::vector<Ticket>());

        // Thu doc file ve cua khach hang
        std::string ticketFilename = "../data/tickets.txt";
        std::ifstream ticketFile(ticketFilename);

        if (ticketFile.is_open()) {
            std::string ticketLine;
            while (std::getline(ticketFile, ticketLine)) {
                if (ticketLine.empty()) continue;

                std::istringstream ticketIss(ticketLine);
                std::string ticketId, priceStr, movieId, seatId, showtimeId, customerId, bookingDate;

                std::getline(ticketIss, ticketId, ',');
                std::getline(ticketIss, priceStr, ',');
                std::getline(ticketIss, movieId, ',');
                std::getline(ticketIss, seatId, ',');
                std::getline(ticketIss, showtimeId, ',');
                std::getline(ticketIss, customerId, ',');
                std::getline(ticketIss, bookingDate);


                if(customerId == customer.getId()){
                    double price = std::stod(priceStr);

                    // Tao doi tuong Seat
                    Seat seat(movieId, seatId, showtimeId, false);

                    // Tao doi tuong Ticket
                    Ticket ticket(ticketId, price, seat, movieId, showtimeId, customerId);
                    ticket.setBookingDate(bookingDate);

                    // Them ve vao danh sach ve cua khach hang
                    customer.addTicket(ticket);
                }
            }
            ticketFile.close();
        }

        // Them khach hang vao danh sach
        customers.push_back(customer);
    }
    file.close();
}


void CustomerService::bookTicket(const std::string &customerId, const Ticket &ticket) {
   Customer customer = getCustomerById(customerId);
   customer.addTicket(ticket);
}

void CustomerService::saveCustomersToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Khong the mo file: " + filename);
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

    // Khoi tao MovieService mot lan duy nhat o ngoai vong lap de toi uu hieu suat
    MovieService movieService;
    try {
        movieService.loadMoviesFromFile("../data/movie.txt");
    } catch (const std::runtime_error& e) {
        std::cerr << "Loi khi tai du lieu phim: " << e.what() << std::endl;
    }

    for (auto& customer : customers) {
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| ID khach hang: " << std::left << std::setw(47) << customer.getId() << "|" << std::endl;
        std::cout << "|-----------------------------------------------------------|" << std::endl;
        std::cout << "| Ten:           " << std::left << std::setw(47) << customer.getName() << "|" << std::endl;
        std::cout << "| So dien thoai: " << std::left << std::setw(47) << customer.getPhone() << "|" << std::endl;
        std::cout << "| Email:         " << std::left << std::setw(47) << customer.getEmail() << "|" << std::endl;

        // Hien thi thong tin ve ve da dat
        std::vector<Ticket> tickets = customer.getTickets();
        std::cout << "|-----------------------------------------------------------|" << std::endl;
        std::cout << "| So ve da dat:  " << std::left << std::setw(47) << tickets.size() << "|" << std::endl;

        if (!tickets.empty()) {
            std::cout << "|-----------------------------------------------------------|" << std::endl;
            std::cout << "| Danh sach ve:                                             |" << std::endl;

            for (auto& ticket : tickets) {
                std::cout << "| - Ma ve: " << std::left << std::setw(49) << ticket.getId() << "|" << std::endl;
                std::cout << "|   Gia:   " << std::left << std::setw(50) << ticket.getPrice() << "|" << std::endl;

                Seat seat = ticket.getSeat();
                std::cout << "| Ghe: " << std::left << std::setw(50) << seat.getId() << "|" << std::endl;
                // Neu Ticket co phuong thuc getMovieId()
                try {
                    // Su dung getMovieId tu Ticket thay vi tu Seat
                    Movie movie = movieService.getMovieById(ticket.getMovieId());
                    std::cout << "|   Phim:  " << std::left << std::setw(50) << movie.getName() << "|" << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cout << "|   Phim:  " << std::left << std::setw(50) << "Khong co thong tin" << "|" << std::endl;
                }

                // Hien thi thong tin suat chieu neu co
                if (ticket.getShowtimeId() != "") {
                    std::cout << "|   Suat:  " << std::left << std::setw(50) << ticket.getShowtimeId() << "|" << std::endl;
                }

                std::cout << "|-----------------------------------------------------------|" << std::endl;
            }
        }

        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "====================== KET THUC ======================" << std::endl;
}


void CustomerService::addCustomerFromKeyboard() {
    std::string id, name, phone, email;

    handle::handle_view_banner_add_customer();

    std::cout << "| ID khach hang: ";
    std::cin >> id;

    std::cin.ignore(); // Loai bo ky tu newline trong buffer

    std::cout << "| Ten khach hang: ";
    std::getline(std::cin, name);

    std::cout << "| So dien thoai: ";
    std::getline(std::cin, phone);

    std::cout << "| Email: ";
    std::getline(std::cin, email);

    // Tao doi tuong Customer moi va them vao danh sach
    addCustomer(Customer(id, name, phone, email, std::vector<Ticket>()));
    // Luu khach hang vao file
    try {
        saveCustomersToFile("../data/customer.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error saving customer data: " << e.what() << std::endl;
    }
    handle::handle_view_alert_add_customer_success();

}

void CustomerService::updateCustomerFromKeyboard() {
    std::string customerId;

    // Hien thi danh sach khach hang de nguoi dung chon
    handle::handle_view_banner_list_customer();
    for (auto& customer : customers) {
        std::cout << "ID: " << customer.getId() << ", Ten: " << customer.getName()
                  << ", SDT: " << customer.getPhone() << ", Email: " << customer.getEmail() << std::endl;
    }

    handle::handle_view_banner_update_customer();

    // Yeu cau ID khach hang can cap nhat
    std::cout << "| Nhap ID khach hang can cap nhat: ";
    std::cin >> customerId;

    // Tim khach hang voi ID da nhap
    bool found = false;
    Customer currentCustomer;

    try {
        currentCustomer = getCustomerById(customerId);
        found = true;
    } catch (const std::runtime_error& e) {
        std::cout << "| Khong tim thay khach hang voi ID: " << customerId << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        return;
    }

    // Hien thi thong tin khach hang hien tai
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                THONG TIN KHACH HANG HIEN TAI              |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "| ID: " << currentCustomer.getId() << std::endl;
    std::cout << "| Ten: " << currentCustomer.getName() << std::endl;
    std::cout << "| SDT: " << currentCustomer.getPhone() << std::endl;
    std::cout << "| Email: " << currentCustomer.getEmail() << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::cin.ignore(); // Xoa buffer

    std::cout << "|          NHAP THONG TIN MOI (DE TRONG DE GIU NGUYEN)      |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::string name, phone, email;

    std::cout << "| Ten khach hang: ";
    std::getline(std::cin, name);
    if (name.empty()) name = currentCustomer.getName();

    std::cout << "| So dien thoai: ";
    std::getline(std::cin, phone);
    if (phone.empty()) phone = currentCustomer.getPhone();

    std::cout << "| Email: ";
    std::getline(std::cin, email);
    if (email.empty()) email = currentCustomer.getEmail();

    // Tao doi tuong Customer moi voi thong tin da cap nhat
    Customer updatedCustomer(customerId, name, phone, email, currentCustomer.getTickets());


    // Cap nhat khach hang
    try {
        updateCustomer(customerId, updatedCustomer);
        saveCustomersToFile("../data/customer.txt");
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "|              CAP NHAT KHACH HANG THANH CONG!              |" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| Loi: " << e.what() << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
    }
}

void CustomerService::removeCustomerFromKeyboard() {
    // Hien thi danh sach khach hang de nguoi dung co the xem ID
    showAllCustomers();

    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                    XOA KHACH HANG                         |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::string customerId;
    std::cout << "| Nhap ID khach hang can xoa: ";
    std::cin >> customerId;

    try {
        // Kiem tra xem khach hang co ton tai khong
        getCustomerById(customerId);

        // Xoa khach hang voi ID tuong ung
        removeCustomer(customerId);
        saveCustomersToFile("../data/customer.txt");
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "|               DA XOA KHACH HANG THANH CONG!               |" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
    } catch (const std::runtime_error& e) {
        // Xu ly truong hop khong tim thay khach hang
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| Loi: Khong tim thay khach hang voi ID: " << customerId << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
    }

    // Xoa buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}



