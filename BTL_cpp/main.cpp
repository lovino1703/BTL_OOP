#include <iostream>
#include <vector>
#include <string>
#include "services/MovieService.h"
#include "services/ShowtimeService.h"
#include "services/TicketService.h"
#include "services/SeatService.h"
#include "services/CustomerService.h"
#include "handle.h"

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

        // Khoi tao TicketService voi cac service khac
        ticketService = TicketService(&movieService, &customerService, &seatService, &showtimeService);

        // Load ticket data sau khi khoi tao
        ticketService.loadTicketsFromFile("../data/tickets.txt");
    } catch (const std::exception &e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
    }
}

void management_seat(){
    int choice;
    do {
        handle::handle_view_seat_management();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
                std::cout << "Returning to admin menu..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

}

void management_customer() {
    int choice;
    do {
        handle::handle_view_customer_management();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
                std::cout << "Returning to admin menu..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

}

void management_mvie() {
    int choice;
    do {
        handle::handle_view_movie_management();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
                std::cout << "Returning to admin menu..." << std::endl;
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
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
                std::cout << "Returning to admin menu..." << std::endl;
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
        std::cout << "Enter your choice: ";
        std::cin >> choice;

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
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                handle::handle_view_alert_choose_invalid();
        }
    } while (choice != 6);
}

void login_as_admin() {
    std::string username, password;
    handle::handle_view_enter_username();
    std::cin >> username;
    handle::handle_view_enter_password();
    std::cin >> password;

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
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                login_as_admin();
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
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

