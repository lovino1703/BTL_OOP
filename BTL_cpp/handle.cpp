//
// Created by admin on 4/25/2025.
//

#include "handle.h"

#include <iostream>

void handle::handle_view_login() {
    std::cout << "+-----------------------+" << std::endl;
    std::cout << "|       LOGIN MENU      |" << std::endl;
    std::cout << "+-----------------------+" << std::endl;
    std::cout << "| 1. Login as Admin     |" << std::endl;
    std::cout << "| 2. Exit               |" << std::endl;
    std::cout << "+-----------------------+" << std::endl;
}

void handle::handle_view_admin_menu() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|       ADMIN MENU          |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| 1. Manage Movies          |" << std::endl;
    std::cout << "| 2. Manage Tickets         |" << std::endl;
    std::cout << "| 3. Manage Seats           |" << std::endl;
    std::cout << "| 4. Manage Customers       |" << std::endl;
    std::cout << "| 5. Logout                 |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_enter_username() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| Enter admin username:     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_enter_password() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| Enter admin password:     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_alert_login_success() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| Login successful!         |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_alert_login_unsuccessful() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| Invalid credentials.      |" << std::endl;
    std::cout << "| Please try again.         |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_alert_choose_invalid() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| Invalid choice.           |" << std::endl;
    std::cout << "| Please try again.         |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_movie_management() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|     MOVIE MANAGEMENT      |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| 1. Add Movie              |" << std::endl;
    std::cout << "| 2. Update Movie           |" << std::endl;
    std::cout << "| 3. Delete Movie           |" << std::endl;
    std::cout << "| 4. View Movies            |" << std::endl;
    std::cout << "| 5. Back to Admin Menu     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_ticket_management() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|     TICKET MANAGEMENT     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| 1. Add Ticket             |" << std::endl;
    std::cout << "| 2. Delete Ticket          |" << std::endl;
    std::cout << "| 3. View Tickets           |" << std::endl;
    std::cout << "| 4. Back to Admin Menu     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_customer_management() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|    CUSTOMER MANAGEMENT    |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| 1. Add Customer           |" << std::endl;
    std::cout << "| 2. Update Customer        |" << std::endl;
    std::cout << "| 3. Delete Customer        |" << std::endl;
    std::cout << "| 4. View Customers         |" << std::endl;
    std::cout << "| 5. Back to Admin Menu     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}

void handle::handle_view_seat_management() {
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "|       SEAT MANAGEMENT     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
    std::cout << "| 1. Add Seat               |" << std::endl;
    std::cout << "| 2. Delete Seat            |" << std::endl;
    std::cout << "| 3. View Seats             |" << std::endl;
    std::cout << "| 4. Reset Seats            |" << std::endl;
    std::cout << "| 5. Back to Admin Menu     |" << std::endl;
    std::cout << "+---------------------------+" << std::endl;
}


void handle::handle_view_banner_update_customer() {
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                    CAP NHAT THONG TIN KHACH HANG          |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
}

void handle::handle_view_banner_list_customer() {
    std::cout << "\n==================== DANH SACH KHACH HANG ====================\n" << std::endl;
}

void handle::handle_view_alert_add_customer_success() {
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|               DA THEM KHACH HANG THANH CONG!              |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
}

void handle::handle_view_banner_add_customer() {
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                    NHAP THONG TIN KHACH HANG              |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
}

void handle::handle_view_banner_empty_customer() {
    std::cout << "\n=== DANH SACH KHACH HANG TRONG ===\n" << std::endl;
}


