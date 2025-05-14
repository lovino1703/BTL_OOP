cmake_minimum_required(VERSION 3.28)
project(BTL_OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(BTL_OOP
        main.cpp
        models/Seat.cpp
        models/Ticket.cpp
        models/Customer.cpp
        models/Movie.cpp
        models/Time.cpp
        services/CustomerService.cpp
        services/MovieService.cpp
        services/ShowtimeService.cpp
        services/TicketService.cpp
        services/SeatService.cpp
        handle.cpp)
