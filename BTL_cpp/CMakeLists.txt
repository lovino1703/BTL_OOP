cmake_minimum_required(VERSION 3.28)
project(BTLPhuc)

set(CMAKE_CXX_STANDARD 11)

add_executable(BTLPhuc main.cpp
        models/Seat.h
        models/Seat.cpp
        models/Ticket.h
        models/Ticket.cpp
        models/Customer.h
        models/Customer.cpp
        models/Movie.h
        models/Movie.cpp
        models/Time.h
        models/Time.cpp
        services/CustomerService.h
        services/CustomerService.cpp
        services/MovieService.h
        services/MovieService.cpp
        services/SeatService.h
        services/ShowtimeService.h
        services/ShowtimeService.cpp
        services/TicketService.h
        services/TicketService.cpp
        services/SeatService.cpp
        handle.cpp)
