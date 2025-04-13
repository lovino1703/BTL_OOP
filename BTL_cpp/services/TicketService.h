// TicketService.h
#ifndef BTLPHUC_TICKETSERVICE_H
#define BTLPHUC_TICKETSERVICE_H

#include <vector>
#include "../models/Ticket.h"
#include "../models/Seat.h"
#include "MovieService.h"
#include "CustomerService.h"
#include "SeatService.h"
#include "ShowtimeService.h"

class TicketService {
private:
    std::vector<Ticket> tickets;
    MovieService* movieService;
    CustomerService* customerService;
    SeatService* seatService;
    ShowtimeService* showtimeService;

public:
    TicketService();
    TicketService(MovieService* movieService, CustomerService* customerService,
                  SeatService* seatService, ShowtimeService* showtimeService);

    void createTicket(std::string ticketId, long price, Seat seat);
    void cancelTicket(std::string ticketId);
    void displayAllTickets();
    void displayTicketDetails(std::string ticketId);

    // Các phương thức mới
    void bookTicket();
    Ticket createTicketWithDetails(std::string customerId, std::string movieId,
                                   std::string seatId, std::string showtimeId);
    bool isTicketAvailable(std::string movieId, std::string seatId, std::string showtimeId);
    double calculateTicketPrice(std::string movieId, std::string seatId);

    void loadTicketsFromFile(const std::string& filename);
    void saveTicketsToFile(const std::string& filename);
    void addTicketFromKeyboard();
    void removeTicketFromKeyboard();
    void showAllTickets();
    void saveCustomersTicketsToFile(std::string basicString, Customer customer);
};

#endif //BTLPHUC_TICKETSERVICE_H
