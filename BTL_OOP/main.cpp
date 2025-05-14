#include <iostream>
#include <vector>
#include <string>
#include "services/MovieService.h"
#include "services/ShowtimeService.h"
#include "services/TicketService.h"
#include "services/SeatService.h"
#include "services/CustomerService.h"
#include "handle.h"

using namespace std;

MovieService movieService;
ShowtimeService showtimeService;
TicketService ticketService;
SeatService seatService;
CustomerService customerService;

void init() {
    showtimeService.addShowtime(Time("ST001", "09:00"));
    showtimeService.addShowtime(Time("ST002", "13:30"));
    showtimeService.addShowtime(Time("ST003", "18:00"));
    showtimeService.addShowtime(Time("ST004", "21:30"));

    // Load data from files
    try {
        movieService.loadMoviesFromFile("../data/movie.txt");
        seatService.loadSeatsFromFile("../data/seats.txt");
        customerService.loadCustomersFromFile("../data/customer.txt");

        // Khởi tạo TicketService với các service khác
        ticketService = TicketService(&movieService, &customerService, &seatService, &showtimeService);

        // Load ticket data sau khi khởi tạo
        ticketService.loadTicketsFromFile("../data/tickets.txt");
    } catch (const exception &e) {
        cerr << "Error loading data: " << e.what() << endl;
    }
}

void management_seat() {
    int choice;
    do {
        handle::handle_view_seat_management();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                seatService.addSeatFromKeyboard();
                break;
            case 2:
                seatService.removeSeatFromKeyboard();
                break;
            case 3:
                seatService.showAllSeats();
                break;
            case 4:
                seatService.resetSeats();
                break;
            case 5:
                cout << "Returning to admin menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

void management_customer() {
    int choice;
    do {
        handle::handle_view_customer_management();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                customerService.addCustomerFromKeyboard();
                break;
            case 2:
                customerService.updateCustomerFromKeyboard();
                break;
            case 3:
                customerService.removeCustomerFromKeyboard();
                break;
            case 4:
                customerService.showAllCustomers();
                break;
            case 5:
                cout << "Returning to admin menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

void management_mvie() {
    int choice;
    do {
        handle::handle_view_movie_management();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                movieService.addMovieFromKeyboard();
                break;
            case 2:
                movieService.updateMovieFromKeyboard();
                break;
            case 3:
                movieService.removeMovieFromKeyboard();
                break;
            case 4:
                movieService.showAllMovies();
                break;
            case 5:
                cout << "Returning to admin menu..." << endl;
                break;
            default:
                handle::handle_view_alert_choose_invalid();
        }
    } while (choice != 5);
}

void managemet_ticket() {
    int choice;
    do {
        handle::handle_view_ticket_management();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ticketService.bookTicket();
                break;
            case 2:
                ticketService.removeTicketFromKeyboard();
                break;
            case 3:
                ticketService.showAllTickets();
                break;
            case 4:
                cout << "Returning to admin menu..." << endl;
                break;
            default:
                handle::handle_view_alert_choose_invalid();
        }
    } while (choice != 4);
}

void menu_admin() {
    int choice;
    do {
        handle::handle_view_admin_menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                management_mvie();
                break;
            case 2:
                managemet_ticket();
                break;
            case 3:
                management_seat();
                break;
            case 4:
                management_customer();
                break;
            case 5:
                cout << "Logging out..." << endl;
                break;
            default:
                handle::handle_view_alert_choose_invalid();
        }
    } while (choice != 6);
}

void login_as_admin() {
    string username, password;
    handle::handle_view_enter_username();
    cin >> username;
    handle::handle_view_enter_password();
    cin >> password;

    if (username == "admin" && password == "admin") {
        handle::handle_view_alert_login_success();
        menu_admin();
    } else {
        handle::handle_view_alert_login_unsuccessful();
    }
}

void menu_login() {
    int choice;
    do {
        handle::handle_view_login();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                login_as_admin();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                handle::handle_view_alert_choose_invalid();
        }
    } while (choice != 3);
}

int main() {
    init();
    menu_login();
}
