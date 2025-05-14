#include "handle.h"
#include <iostream>

using namespace std;

void handle::handle_view_login() {
    cout << "+-----------------------+" << endl;
    cout << "|       LOGIN MENU      |" << endl;
    cout << "+-----------------------+" << endl;
    cout << "| 1. Login as Admin     |" << endl;
    cout << "| 2. Exit               |" << endl;
    cout << "+-----------------------+" << endl;
}

void handle::handle_view_admin_menu() {
    cout << "+---------------------------+" << endl;
    cout << "|       ADMIN MENU          |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "| 1. Manage Movies          |" << endl;
    cout << "| 2. Manage Tickets         |" << endl;
    cout << "| 3. Manage Seats           |" << endl;
    cout << "| 4. Manage Customers       |" << endl;
    cout << "| 5. Logout                 |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_enter_username() {
    cout << "+---------------------------+" << endl;
    cout << "| Enter admin username:     |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_enter_password() {
    cout << "+---------------------------+" << endl;
    cout << "| Enter admin password:     |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_alert_login_success() {
    cout << "+---------------------------+" << endl;
    cout << "| Login successful!         |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_alert_login_unsuccessful() {
    cout << "+---------------------------+" << endl;
    cout << "| Invalid credentials.      |" << endl;
    cout << "| Please try again.         |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_alert_choose_invalid() {
    cout << "+---------------------------+" << endl;
    cout << "| Invalid choice.           |" << endl;
    cout << "| Please try again.         |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_movie_management() {
    cout << "+---------------------------+" << endl;
    cout << "|     MOVIE MANAGEMENT      |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "| 1. Add Movie              |" << endl;
    cout << "| 2. Update Movie           |" << endl;
    cout << "| 3. Delete Movie           |" << endl;
    cout << "| 4. View Movies            |" << endl;
    cout << "| 5. Back to Admin Menu     |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_ticket_management() {
    cout << "+---------------------------+" << endl;
    cout << "|     TICKET MANAGEMENT     |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "| 1. Add Ticket             |" << endl;
    cout << "| 2. Delete Ticket          |" << endl;
    cout << "| 3. View Tickets           |" << endl;
    cout << "| 4. Back to Admin Menu     |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_customer_management() {
    cout << "+---------------------------+" << endl;
    cout << "|    CUSTOMER MANAGEMENT    |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "| 1. Add Customer           |" << endl;
    cout << "| 2. Update Customer        |" << endl;
    cout << "| 3. Delete Customer        |" << endl;
    cout << "| 4. View Customers         |" << endl;
    cout << "| 5. Back to Admin Menu     |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_seat_management() {
    cout << "+---------------------------+" << endl;
    cout << "|       SEAT MANAGEMENT     |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "| 1. Add Seat               |" << endl;
    cout << "| 2. Delete Seat            |" << endl;
    cout << "| 3. View Seats             |" << endl;
    cout << "| 4. Reset Seats            |" << endl;
    cout << "| 5. Back to Admin Menu     |" << endl;
    cout << "+---------------------------+" << endl;
}

void handle::handle_view_banner_update_customer() {
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                    CAP NHAT THONG TIN KHACH HANG          |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
}

void handle::handle_view_banner_list_customer() {
    cout << "\n==================== DANH SACH KHACH HANG ====================\n" << endl;
}

void handle::handle_view_alert_add_customer_success() {
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|               DA THEM KHACH HANG THANH CONG!              |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
}

void handle::handle_view_banner_add_customer() {
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                    NHAP THONG TIN KHACH HANG              |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
}

void handle::handle_view_banner_empty_customer() {
    cout << "\n=== DANH SACH KHACH HANG TRONG ===\n" << endl;
}


