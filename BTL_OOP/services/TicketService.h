#ifndef TICKETSERVICE_H
#define TICKETSERVICE_H

#include <vector>
#include "../models/Ticket.h"
#include "../models/Seat.h"
#include "MovieService.h"
#include "CustomerService.h"
#include "SeatService.h"
#include "ShowtimeService.h"

using namespace std;

class TicketService {
private:
    vector<Ticket> tickets;
    MovieService* movieService;
    CustomerService* customerService;
    SeatService* seatService;
    ShowtimeService* showtimeService;

public:
    TicketService();
    TicketService(MovieService* movieService, CustomerService* customerService,
                  SeatService* seatService, ShowtimeService* showtimeService);

    void createTicket(string ticketId, long price, Seat seat);
    void cancelTicket(string ticketId);
    void displayAllTickets();
    void displayTicketDetails(string ticketId);

    // Các phương thức mới
    void bookTicket();
    Ticket createTicketWithDetails(string customerId, string movieId,
                                   string seatId, string showtimeId);
    bool isTicketAvailable(string movieId, string seatId, string showtimeId);
    double calculateTicketPrice(string movieId, string seatId);

    void loadTicketsFromFile(const string& filename);
    void saveTicketsToFile(const string& filename);
    void addTicketFromKeyboard();
    void removeTicketFromKeyboard();
    void showAllTickets();
    void saveCustomersTicketsToFile(string basicString, Customer customer);
};

#endif //TICKETSERVICE_H
