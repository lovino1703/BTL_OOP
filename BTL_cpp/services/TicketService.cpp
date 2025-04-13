// TicketService.cpp
#include "TicketService.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

TicketService::TicketService() {}

TicketService::TicketService(MovieService *movieService, CustomerService *customerService,
                             SeatService *seatService, ShowtimeService *showtimeService) {
    this->movieService = movieService;
    this->customerService = customerService;
    this->seatService = seatService;
    this->showtimeService = showtimeService;
}

void TicketService::createTicket(std::string ticketId, long price, Seat seat) {
    Ticket ticket(ticketId, price, seat);
    tickets.push_back(ticket);
}

void TicketService::cancelTicket(std::string ticketId) {
    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->getId() == ticketId) {
            tickets.erase(it);
            return;
        }
    }
}

void TicketService::displayAllTickets() {
    for (auto &ticket: tickets) {
        std::cout << "Ticket ID: " << ticket.getId()
                  << ", Price: " << ticket.getPrice()
                  << ", Seat ID: " << ticket.getSeat().getId() << std::endl;
    }
}

void TicketService::bookTicket() {
    std::cout << "\n==================== DAT VE XEM PHIM ====================\n" << std::endl;

    // 1. Hien thi danh sach phim
    movieService->showAllMovies();

    // 2. Chon phim
    std::string movieId;
    std::cout << "\nNhap ID phim ban muon xem: ";
    std::cin >> movieId;

    Movie selectedMovie;
    try {
        selectedMovie = movieService->getMovieById(movieId);
    } catch (const std::runtime_error &e) {
        std::cout << "Loi: " << e.what() << std::endl;
        return;
    }

    // 3. Hien thi cac suat chieu
    std::cout << "\nCac suat chieu cho phim " << selectedMovie.getName() << ":\n";
    std::vector<Time> showtimes = showtimeService->getAllShowtimes();
    for (int i = 0; i < showtimes.size(); i++) {
        std::cout << i + 1 << ". ID: " << showtimes[i].getId()
                  << ", Thoi gian bat dau: " << showtimes[i].getStartTime() << std::endl;
    }

    // 4. Chon suat chieu
    int showtimeChoice;
    std::cout << "\nChon suat chieu (1-" << showtimes.size() << "): ";
    std::cin >> showtimeChoice;

    if (showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
        std::cout << "Lua chon khong hop le!" << std::endl;
        return;
    }

    std::string showtimeId = showtimes[showtimeChoice - 1].getId();

    // 5. Hien thi cac ghe co san
    std::cout << "\nCac ghe co san cho suat chieu nay:\n";
    std::vector<Seat> seats = seatService->getAllSeats();

    std::cout << "+-------------------------------------------+" << std::endl;
    std::cout << "|                MAN HINH                   |" << std::endl;
    std::cout << "+-------------------------------------------+" << std::endl;

    char currentRow = 'A';
    int seatsPerRow = 5;

    for (char row = 'A'; row <= 'E'; row++) {
        std::cout << row << " | ";
        for (int col = 1; col <= seatsPerRow; col++) {
            bool found = false;
            bool available = true;

            std::string seatId = std::string(1, row) + std::to_string(col);

            for (auto &seat: seats) {
                if (seat.getId() == seatId && seat.getMovieId() == movieId) {
                    found = true;
                    available = seat.getIsAvailable();
                    break;
                }
            }

            if (found && available)
                std::cout << " O ";
            else if (found && !available)
                std::cout << " X ";
            else
                std::cout << " - ";
        }
        std::cout << " |" << std::endl;
    }

    std::cout << "+-------------------------------------------+" << std::endl;
    std::cout << "Chu thich: O = Ghe trong, X = Ghe da dat, - = Khong co ghe\n";

    // 6. Chon ghe
    std::string seatId;
    std::cout << "\nNhap ID ghe ban muon dat (vi du: A1, B3): ";
    std::cin >> seatId;

    // 7. Kiem tra xem ghe co san khong
    if (!isTicketAvailable(movieId, seatId, showtimeId)) {
        std::cout << "Ghe nay da duoc dat hoac khong ton tai!" << std::endl;
        return;
    }

    // 8. Nhap thong tin khach hang
    customerService->showAllCustomers();
    std::string customerId;
    std::cout << "\nNhap ID khach hang (hoac nhap 'new' de tao moi): ";
    std::cin >> customerId;

    Customer customer;
    if (customerId == "new") {
        customerService->addCustomerFromKeyboard();
        // Lay ID khach hang vua them
        std::vector<Customer> customers = customerService->getAllCustomers();
        customerId = customers.back().getId();
    }

    try {
        customer = customerService->getCustomerById(customerId);
    } catch (const std::runtime_error &e) {
        std::cout << "Khach hang khong ton tai. Vui long dang ky tai khoan truoc khi dat ve." << std::endl;
        return;
    }

    // 9. Tinh gia ve
    double price = calculateTicketPrice(movieId, seatId);
    std::cout << "\nGia ve: " << price << " VND" << std::endl;

    // 10. Xac nhan dat ve
    char confirm;
    std::cout << "\nXac nhan dat ve? (Y/N): ";
    std::cin >> confirm;

    if (confirm != 'Y' && confirm != 'y') {
        std::cout << "Da huy dat ve." << std::endl;
        return;
    }

    // 11. Tao ghe neu chua ton tai
    bool seatExists = false;
    Seat selectedSeat;

    for (const auto &seat: seats) {
        if (seat.getId() == seatId && seat.getMovieId() == movieId) {
            seatExists = true;
            selectedSeat = seat;
            break;
        }
    }

    if (!seatExists) {
        selectedSeat = Seat(movieId, seatId, showtimeId, true);
        seatService->addSeat(selectedSeat);
    }

    // 12. Tao ve moi
    std::string ticketId = "TK" + std::to_string(time(nullptr));
    Ticket newTicket = createTicketWithDetails(customerId, movieId, seatId, showtimeId);

    // 13. Them ve cho khach hang
    try {
        customerService->bookTicket(customerId, newTicket);
    } catch (const std::runtime_error &e) {
        std::cout << "Loi khi dat ve: " << e.what() << std::endl;
        return;
    }

    // 14. Dat ghe
    seatService->reserveSeat(seatId);

    // 15. Them ve vao danh sach ve
    tickets.push_back(newTicket);

    // 16. Luu thong tin vao file
    try {
        saveTicketsToFile("../data/tickets.txt");
        seatService->saveSeatsToFile("../data/seats.txt");
    } catch (const std::runtime_error &e) {
        std::cerr << "Lỗi khi lưu dữ liệu: " << e.what() << std::endl;
    }


    // 17. Hien thi chi tiet ve
    std::cout << "\n==================== THONG TIN VE ====================\n" << std::endl;
    std::cout << "ID Ve: " << ticketId << std::endl;
    std::cout << "Ten phim: " << selectedMovie.getName() << std::endl;
    std::cout << "Suat chieu: " << showtimeId << std::endl;
    std::cout << "Ghe: " << seatId << std::endl;
    std::cout << "Gia ve: " << price << " VND" << std::endl;
    std::cout << "Khach hang: " << customer.getName() << std::endl;
    std::cout << "Ngay dat: " << newTicket.getBookingDate() << std::endl;

    std::cout << "\nDat ve thanh cong!" << std::endl;
}

Ticket TicketService::createTicketWithDetails(std::string customerId, std::string movieId,
                                              std::string seatId, std::string showtimeId) {
    // Tạo ID vé duy nhất
    std::string ticketId = "TK" + std::to_string(time(nullptr));

    // Lấy thông tin về phim, ghế và suất chiếu
    Movie movie = movieService->getMovieById(movieId);
    Seat seat;
    bool seatFound = false;

    for (const auto &s: seatService->getAllSeats()) {
        if (s.getId() == seatId && s.getMovieId() == movieId) {
            seat = s;
            seatFound = true;
            break;
        }
    }

    if (!seatFound) {
        seat = Seat(movieId, seatId, showtimeId, true);
    }

    // Tính giá vé dựa trên thông tin phim và loại ghế
    double price = calculateTicketPrice(movieId, seatId);

    // Tạo và trả về vé
    Ticket ticket(ticketId, price, seat, movieId, showtimeId, customerId);
    return ticket;
}

void TicketService::displayTicketDetails(std::string ticketId) {
    for (const auto &ticket: tickets) {
        if (ticket.getId() == ticketId) {
            std::cout << "\n==================== THÔNG TIN VÉ ====================\n" << std::endl;
            std::cout << "ID Vé: " << ticket.getId() << std::endl;

            try {
                Movie movie = movieService->getMovieById(ticket.getMovieId());
                std::cout << "Tên phim: " << movie.getName() << std::endl;
            } catch (const std::runtime_error &e) {
                std::cout << "Phim: Không có thông tin" << std::endl;
            }

            std::cout << "Suất chiếu: " << ticket.getShowtimeId() << std::endl;
            std::cout << "Ghế: " << ticket.getSeat().getId() << std::endl;
            std::cout << "Giá vé: " << ticket.getPrice() << " VND" << std::endl;

            try {
                Customer customer = customerService->getCustomerById(ticket.getCustomerId());
                std::cout << "Khách hàng: " << customer.getName() << std::endl;
            } catch (const std::runtime_error &e) {
                std::cout << "Khách hàng: Không có thông tin" << std::endl;
            }

            std::cout << "Ngày đặt: " << ticket.getBookingDate() << std::endl;
            return;
        }
    }

    std::cout << "Không tìm thấy vé với ID: " << ticketId << std::endl;
}

bool TicketService::isTicketAvailable(std::string movieId, std::string seatId, std::string showtimeId) {
    // Kiểm tra xem ghế đã được đặt chưa
    std::vector<Seat> seats = seatService->getAllSeats();

    for (auto &seat: seats) {
        if (seat.getId() == seatId && seat.getMovieId() == movieId && !seat.getIsAvailable()) {
            return false;
        }
    }

    // Kiểm tra xem vé đã tồn tại chưa
    for (const auto &ticket: tickets) {
        if (ticket.getSeat().getId() == seatId &&
            ticket.getMovieId() == movieId &&
            ticket.getShowtimeId() == showtimeId) {
            return false;
        }
    }

    return true;
}

double TicketService::calculateTicketPrice(std::string movieId, std::string seatId) {
    // Giá cơ bản
    double basePrice = 100000; // 100,000 VND

    // Thêm giá dựa trên phim (ví dụ: phim mới phát hành có giá cao hơn)
    try {
        Movie movie = movieService->getMovieById(movieId);
        if (movie.getRating() > 8.0) {
            basePrice += 20000; // Thêm 20,000 VND cho phim được đánh giá cao
        }
    } catch (const std::runtime_error &e) {
        // Không tìm thấy phim, giữ nguyên giá cơ bản
    }

    // Thêm giá dựa trên loại ghế
    if (seatId[0] == 'A' || seatId[0] == 'B') {
        basePrice += 50000; // Ghế VIP có giá cao hơn
    }

    return basePrice;
}

void TicketService::loadTicketsFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Tạo file nếu không tồn tại
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            throw std::runtime_error("Không thể tạo file: " + filename);
        }
        outFile.close();
        return;
    }

    tickets.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string id, movieId, seatId, showtimeId, customerId, bookingDate, priceStr;

        std::getline(iss, id, ',');
        std::getline(iss, priceStr, ',');
        std::getline(iss, movieId, ',');
        std::getline(iss, seatId, ',');
        std::getline(iss, showtimeId, ',');
        std::getline(iss, customerId, ',');
        std::getline(iss, bookingDate);

        double price = std::stod(priceStr);

        // Tạo đối tượng Seat
        Seat seat(movieId, seatId, showtimeId, false);

        // Tạo đối tượng Ticket
        Ticket ticket(id, price, seat, movieId, showtimeId, customerId);
        ticket.setBookingDate(bookingDate);

        tickets.push_back(ticket);
    }

    file.close();
}

void TicketService::saveTicketsToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Không thể mở file: " + filename);
    }

    for (const auto &ticket: tickets) {
        file << ticket.getId() << ","
             << ticket.getPrice() << ","
             << ticket.getMovieId() << ","
             << ticket.getSeat().getId() << ","
             << ticket.getShowtimeId() << ","
             << ticket.getCustomerId() << ","
             << ticket.getBookingDate() << "\n";
    }

    file.close();
}

void TicketService::showAllTickets() {
    if (tickets.empty()) {
        std::cout << "\n=== KHONG CO VE NAO TRONG HE THONG ===\n" << std::endl;
        return;
    }

    std::cout << "\n==================== DANH SACH VE ====================\n" << std::endl;

    for (const auto &ticket: tickets) {
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| ID ve: " << std::left << std::setw(53) << ticket.getId() << "|" << std::endl;
        std::cout << "|-----------------------------------------------------------|" << std::endl;

        // Kiem tra null pointer truoc khi su dung movieService
        if (movieService != nullptr) {
            try {
                Movie movie = movieService->getMovieById(ticket.getMovieId());
                std::cout << "| Phim: " << std::left << std::setw(53) << movie.getName() << "|" << std::endl;
            } catch (const std::runtime_error &e) {
                std::cout << "| Phim: " << std::left << std::setw(53) << "Khong co thong tin" << "|" << std::endl;
            }
        } else {
            std::cout << "| Phim: " << std::left << std::setw(53) << "Khong co thong tin" << "|" << std::endl;
        }

        std::cout << "| Suat chieu: " << std::left << std::setw(47) << ticket.getShowtimeId() << "|" << std::endl;
        std::cout << "| Ghe: " << std::left << std::setw(54) << ticket.getSeat().getId() << "|" << std::endl;
        std::cout << "| Gia ve: " << std::left << std::setw(51) << (std::to_string(ticket.getPrice()) + " VND") << "|"
                  << std::endl;

        // Kiem tra null pointer truoc khi su dung customerService
        if (customerService != nullptr) {
            try {
                Customer customer = customerService->getCustomerById(ticket.getCustomerId());
                std::cout << "| Khach hang: " << std::left << std::setw(46) << customer.getName() << "|" << std::endl;
            } catch (const std::runtime_error &e) {
                std::cout << "| Khach hang: " << std::left << std::setw(46) << "Khong co thong tin" << "|" << std::endl;
            }
        } else {
            std::cout << "| Khach hang: " << std::left << std::setw(46) << "Khong co thong tin" << "|" << std::endl;
        }

        std::cout << "| Ngay dat: " << std::left << std::setw(48) << ticket.getBookingDate() << "|" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "====================== KET THUC ======================" << std::endl;
}


void TicketService::addTicketFromKeyboard() {
    // Hiển thị danh sách phim
    movieService->showAllMovies();

    std::string movieId;
    std::cout << "Nhập ID phim: ";
    std::cin >> movieId;

    // Hiển thị danh sách khách hàng
    customerService->showAllCustomers();

    std::string customerId;
    std::cout << "Nhập ID khách hàng: ";
    std::cin >> customerId;

    // Nhập thông tin ghế
    std::string seatId;
    std::cout << "Nhập ID ghế (ví dụ: A1, B2): ";
    std::cin >> seatId;

    // Hiển thị suất chiếu
    std::vector<Time> showtimes = showtimeService->getAllShowtimes();
    std::cout << "Các suất chiếu có sẵn:\n";
    for (int i = 0; i < showtimes.size(); i++) {
        std::cout << i + 1 << ". ID: " << showtimes[i].getId()
                  << ", Thời gian bắt đầu: " << showtimes[i].getStartTime() << std::endl;
    }

    int showtimeChoice;
    std::cout << "Chọn suất chiếu (1-" << showtimes.size() << "): ";
    std::cin >> showtimeChoice;

    if (showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
        std::cout << "Lựa chọn không hợp lệ!" << std::endl;
        return;
    }

    std::string showtimeId = showtimes[showtimeChoice - 1].getId();

    // Tính giá vé
    double price = calculateTicketPrice(movieId, seatId);
    std::cout << "Giá vé: " << price << " VND" << std::endl;

    // Tạo ghế mới nếu chưa tồn tại
    Seat newSeat(movieId, seatId, showtimeId, true);
    seatService->addSeat(newSeat);

    // Tạo vé mới
    std::string ticketId = "TK" + std::to_string(time(nullptr));
    Ticket newTicket(ticketId, price, newSeat, movieId, showtimeId, customerId);

    // Thêm vé vào danh sách
    tickets.push_back(newTicket);

    // Đặt ghế
    seatService->reserveSeat(seatId);

    // Thêm vé cho khách hàng
    try {
        customerService->bookTicket(customerId, newTicket);
    } catch (const std::runtime_error &e) {
        std::cout << "Lỗi khi đặt vé: " << e.what() << std::endl;
        return;
    }

    // Lưu thông tin vào file
    saveTicketsToFile("../data/tickets.txt");
    seatService->saveSeatsToFile("../data/seats.txt");

    std::cout << "\nĐã thêm vé thành công!" << std::endl;
}

void TicketService::removeTicketFromKeyboard() {
    // Hiển thị danh sách vé
    showAllTickets();

    std::string ticketId;
    std::cout << "Nhập ID vé cần hủy: ";
    std::cin >> ticketId;

    // Tìm vé cần hủy
    bool found = false;
    Ticket ticketToCancel;

    for (const auto &ticket: tickets) {
        if (ticket.getId() == ticketId) {
            found = true;
            ticketToCancel = ticket;
            break;
        }
    }

    if (!found) {
        std::cout << "Không tìm thấy vé với ID: " << ticketId << std::endl;
        return;
    }

    // Hủy đặt ghế
    seatService->cancelReservation(ticketToCancel.getSeat().getId());

    // Xóa vé
    cancelTicket(ticketId);

    // Lưu thông tin vào file
    saveTicketsToFile("../data/tickets.txt");
    seatService->saveSeatsToFile("../data/seats.txt");

    std::cout << "\nĐã hủy vé thành công!" << std::endl;
}