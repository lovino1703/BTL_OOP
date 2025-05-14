#include "TicketService.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

TicketService::TicketService() {}

TicketService::TicketService(MovieService *movieService, CustomerService *customerService,
                             SeatService *seatService, ShowtimeService *showtimeService) {
    this->movieService = movieService;
    this->customerService = customerService;
    this->seatService = seatService;
    this->showtimeService = showtimeService;
}

void TicketService::createTicket(string ticketId, long price, Seat seat) {
    Ticket ticket(ticketId, price, seat);
    tickets.push_back(ticket);
}

void TicketService::cancelTicket(string ticketId) {
    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->getId() == ticketId) {
            tickets.erase(it);
            return;
        }
    }
}

void TicketService::displayAllTickets() {
    for (auto &ticket: tickets) {
        cout << "Ticket ID: " << ticket.getId()
             << ", Price: " << ticket.getPrice()
             << ", Seat ID: " << ticket.getSeat().getId() << endl;
    }
}

void TicketService::bookTicket() {
    cout << "\n==================== DAT VE XEM PHIM ====================\n" << endl;

    // 1. Hien thi danh sach phim
    movieService->showAllMovies();

    // 2. Chon phim
    string movieId;
    cout << "\nNhap ID phim ban muon xem: ";
    cin >> movieId;

    Movie selectedMovie;
    try {
        selectedMovie = movieService->getMovieById(movieId);
    } catch (const runtime_error &e) {
        cout << "Loi: " << e.what() << endl;
        return;
    }

    // 3. Hien thi cac suat chieu
    cout << "\nCac suat chieu cho phim " << selectedMovie.getName() << ":\n";
    vector<Time> showtimes = showtimeService->getAllShowtimes();
    for (int i = 0; i < showtimes.size(); i++) {
        cout << i + 1 << ". ID: " << showtimes[i].getId()
             << ", Thoi gian bat dau: " << showtimes[i].getStartTime() << endl;
    }

    // 4. Chon suat chieu
    int showtimeChoice;
    cout << "\nChon suat chieu (1-" << showtimes.size() << "): ";
    cin >> showtimeChoice;

    if (showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
        cout << "Lua chon khong hop le!" << endl;
        return;
    }

    string showtimeId = showtimes[showtimeChoice - 1].getId();

    // 5. Hien thi cac ghe co san
    cout << "\nCac ghe co san cho suat chieu nay:\n";
    vector<Seat> seats = seatService->getAllSeats();

    cout << "+-------------------------------------------+" << endl;
    cout << "|                MAN HINH                   |" << endl;
    cout << "+-------------------------------------------+" << endl;

    char currentRow = 'A';
    int seatsPerRow = 5;

    for (char row = 'A'; row <= 'E'; row++) {
        cout << row << " | ";
        for (int col = 1; col <= seatsPerRow; col++) {
            bool found = false;
            bool available = true;

            string seatId = string(1, row) + to_string(col);

            for (auto &seat: seats) {
                if (seat.getId() == seatId && seat.getMovieId() == movieId && seat.getShowtimeId() == showtimeId) {
                    found = true;
                    available = seat.getIsAvailable();
                    break;
                }
            }

            if (found && available)
                cout << " O ";
            else if (found && !available)
                cout << " X ";
            else
                cout << " - ";
        }
        cout << " |" << endl;
    }

    cout << "+-------------------------------------------+" << endl;
    cout << "Chu thich: O = Ghe trong, X = Ghe da dat, - = Khong co ghe\n";

    // 6. Chon ghe
    string seatId;
    cout << "\nNhap ID ghe ban muon dat (vi du: A1, B3): ";
    cin >> seatId;

    if (seatId.length() < 2 || seatId[0] < 'A' || seatId[0] > 'E' || seatId.substr(1).find_first_not_of("0123456789") != string::npos) {
        cout << "ID ghe khong hop le!" << endl;
        return;
    }

    // 7. Kiem tra xem ghe co san khong
    if (!isTicketAvailable(movieId, seatId, showtimeId)) {
        cout << "Ghe nay da duoc dat hoac khong ton tai!" << endl;
        return;
    }

    // 8. Nhap thong tin khach hang
    customerService->showAllCustomers();
    string customerId;
    cout << "\nNhap ID khach hang (hoac nhap 'new' de tao moi): ";
    cin >> customerId;

    Customer customer;
    if (customerId == "new") {
        customerService->addCustomerFromKeyboard();
        // Lay ID khach hang vua them
        vector<Customer> customers = customerService->getAllCustomers();
        customerId = customers.back().getId();
    }

    try {
        customer = customerService->getCustomerById(customerId);
    } catch (const runtime_error &e) {
        cout << "Khach hang khong ton tai. Vui long dang ky tai khoan truoc khi dat ve." << endl;
        return;
    }

    // 9. Tinh gia ve
    double price = calculateTicketPrice(movieId, seatId);
    cout << "\nGia ve: " << price << " VND" << endl;

    // 10. Xac nhan dat ve
    char confirm;
    cout << "\nXac nhan dat ve? (Y/N): ";
    cin >> confirm;

    if (confirm != 'Y' && confirm != 'y') {
        cout << "Da huy dat ve." << endl;
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
        selectedSeat = Seat(movieId, seatId, showtimeId, false);
        seatService->addSeat(selectedSeat);
    }

    // 12. Tao ve moi
    string ticketId = "TK" + to_string(time(nullptr));
    Ticket newTicket = createTicketWithDetails(customerId, movieId, seatId, showtimeId);

    // 13. Them ve cho khach hang
    try {
        customerService->bookTicket(customerId, newTicket);
    } catch (const runtime_error &e) {
        cout << "Loi khi dat ve: " << e.what() << endl;
        return;
    }

    // 14. Dat ghe
    seatService->reserveSeat(seatId, showtimeId, movieId);

    // 15. Them ve vao danh sach ve
    tickets.push_back(newTicket);

    // 16. Luu thong tin vao file
    try {
        saveTicketsToFile("../data/tickets.txt");
        seatService->saveSeatsToFile("../data/seats.txt");
    } catch (const runtime_error &e) {
        cerr << "Lỗi khi lưu dữ liệu: " << e.what() << endl;
    }

    // 17. Hien thi chi tiet ve
    cout << "\n==================== THONG TIN VE ====================\n" << endl;
    cout << "ID Ve: " << ticketId << endl;
    cout << "Ten phim: " << selectedMovie.getName() << endl;
    cout << "Suat chieu: " << showtimeId << endl;
    cout << "Ghe: " << seatId << endl;
    cout << "Gia ve: " << price << " VND" << endl;
    cout << "Khach hang: " << customer.getName() << endl;
    cout << "Ngay dat: " << newTicket.getBookingDate() << endl;

    cout << "\nDat ve thanh cong!" << endl;
}

Ticket TicketService::createTicketWithDetails(string customerId, string movieId,
                                              string seatId, string showtimeId) {
    string ticketId = "TK" + to_string(time(nullptr));

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

    double price = calculateTicketPrice(movieId, seatId);

    Ticket ticket(ticketId, price, seat, movieId, showtimeId, customerId);
    return ticket;
}

void TicketService::displayTicketDetails(string ticketId) {
    for (const auto &ticket: tickets) {
        if (ticket.getId() == ticketId) {
            cout << "\n==================== THÔNG TIN VÉ ====================\n" << endl;
            cout << "ID Vé: " << ticket.getId() << endl;

            try {
                Movie movie = movieService->getMovieById(ticket.getMovieId());
                cout << "Tên phim: " << movie.getName() << endl;
            } catch (const runtime_error &e) {
                cout << "Phim: Không có thông tin" << endl;
            }

            cout << "Suất chiếu: " << ticket.getShowtimeId() << endl;
            cout << "Ghế: " << ticket.getSeat().getId() << endl;
            cout << "Giá vé: " << ticket.getPrice() << " VND" << endl;

            try {
                Customer customer = customerService->getCustomerById(ticket.getCustomerId());
                cout << "Khách hàng: " << customer.getName() << endl;
            } catch (const runtime_error &e) {
                cout << "Khách hàng: Không có thông tin" << endl;
            }

            cout << "Ngày đặt: " << ticket.getBookingDate() << endl;
            return;
        }
    }

    cout << "Không tìm thấy vé với ID: " << ticketId << endl;
}

bool TicketService::isTicketAvailable(string movieId, string seatId, string showtimeId) {
    vector<Seat> seats = seatService->getAllSeats();
    bool found = false;

    for (auto &seat: seats) {
        if (seat.getId() == seatId && seat.getMovieId() == movieId && !seat.getIsAvailable() && seat.getShowtimeId() == showtimeId) {
            return false;
        }
        if (seat.getId() == seatId && seat.getMovieId() == movieId && seat.getShowtimeId() == showtimeId) {
            found = true;
        }
    }
    if (!found) {
        return false;
    }

    for (const auto &ticket: tickets) {
        if (ticket.getSeat().getId() == seatId &&
            ticket.getMovieId() == movieId &&
            ticket.getShowtimeId() == showtimeId) {
            return false;
        }
    }

    return true;
}

double TicketService::calculateTicketPrice(string movieId, string seatId) {
    double basePrice = 100000;

    try {
        Movie movie = movieService->getMovieById(movieId);
        if (movie.getRating() > 8.0) {
            basePrice += 20000;
        }
    } catch (const runtime_error &e) {
        // Không tìm thấy phim, giữ nguyên giá cơ bản
    }

    if (seatId[0] == 'A' || seatId[0] == 'B') {
        basePrice += 50000;
    }

    return basePrice;
}

void TicketService::loadTicketsFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            throw runtime_error("Không thể tạo file: " + filename);
        }
        outFile.close();
        return;
    }

    tickets.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string id, movieId, seatId, showtimeId, customerId, bookingDate, priceStr;

        getline(iss, id, ',');
        getline(iss, priceStr, ',');
        getline(iss, movieId, ',');
        getline(iss, seatId, ',');
        getline(iss, showtimeId, ',');
        getline(iss, customerId, ',');
        getline(iss, bookingDate);

        double price = stod(priceStr);

        Seat seat(movieId, seatId, showtimeId, false);

        Ticket ticket(id, price, seat, movieId, showtimeId, customerId);
        ticket.setBookingDate(bookingDate);

        tickets.push_back(ticket);
    }

    file.close();
}

void TicketService::saveTicketsToFile(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Không thể mở file: " + filename);
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
        cout << "\n=== KHONG CO VE NAO TRONG HE THONG ===\n" << endl;
        return;
    }

    cout << "\n==================== DANH SACH VE ====================\n" << endl;

    for (const auto &ticket: tickets) {
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "| ID ve: " << left << setw(53) << ticket.getId() << "|" << endl;
        cout << "|-----------------------------------------------------------|" << endl;

        if (movieService != nullptr) {
            try {
                Movie movie = movieService->getMovieById(ticket.getMovieId());
                cout << "| Phim: " << left << setw(53) << movie.getName() << "|" << endl;
            } catch (const runtime_error &e) {
                cout << "| Phim: " << left << setw(53) << "Khong co thong tin" << "|" << endl;
            }
        } else {
            cout << "| Phim: " << left << setw(53) << "Khong co thong tin" << "|" << endl;
        }

        cout << "| Suat chieu: " << left << setw(47) << ticket.getShowtimeId() << "|" << endl;
        cout << "| Ghe: " << left << setw(54) << ticket.getSeat().getId() << "|" << endl;
        cout << "| Gia ve: " << left << setw(51) << (to_string(ticket.getPrice()) + " VND") << "|"
             << endl;

        if (customerService != nullptr) {
            try {
                Customer customer = customerService->getCustomerById(ticket.getCustomerId());
                cout << "| Khach hang: " << left << setw(46) << customer.getName() << "|" << endl;
            } catch (const runtime_error &e) {
                cout << "| Khach hang: " << left << setw(46) << "Khong co thong tin" << "|" << endl;
            }
        } else {
            cout << "| Khach hang: " << left << setw(46) << "Khong co thong tin" << "|" << endl;
        }

        cout << "| Ngay dat: " << left << setw(48) << ticket.getBookingDate() << "|" << endl;
        cout << "+-----------------------------------------------------------+" << endl;
        cout << endl;
    }

    cout << "====================== KET THUC ======================" << endl;
}

void TicketService::addTicketFromKeyboard() {
    movieService->showAllMovies();

    string movieId;
    cout << "Nhập ID phim: ";
    cin >> movieId;

    customerService->showAllCustomers();

    string customerId;
    cout << "Nhập ID khách hàng: ";
    cin >> customerId;

    string seatId;
    cout << "Nhập ID ghế (ví dụ: A1, B2): ";
    cin >> seatId;

    vector<Time> showtimes = showtimeService->getAllShowtimes();
    cout << "Các suất chiếu có sẵn:\n";
    for (int i = 0; i < showtimes.size(); i++) {
        cout << i + 1 << ". ID: " << showtimes[i].getId()
             << ", Thời gian bắt đầu: " << showtimes[i].getStartTime() << endl;
    }

    int showtimeChoice;
    cout << "Chọn suất chiếu (1-" << showtimes.size() << "): ";
    cin >> showtimeChoice;

    if (showtimeChoice < 1 || showtimeChoice > showtimes.size()) {
        cout << "Lựa chọn không hợp lệ!" << endl;
        return;
    }

    string showtimeId = showtimes[showtimeChoice - 1].getId();

    double price = calculateTicketPrice(movieId, seatId);
    cout << "Giá vé: " << price << " VND" << endl;

    Seat newSeat(movieId, seatId, showtimeId, true);
    seatService->addSeat(newSeat);

    string ticketId = "TK" + to_string(time(nullptr));
    Ticket newTicket(ticketId, price, newSeat, movieId, showtimeId, customerId);

    tickets.push_back(newTicket);

    seatService->reserveSeat(seatId, showtimeId, movieId);

    try {
        customerService->bookTicket(customerId, newTicket);
    } catch (const runtime_error &e) {
        cout << "Lỗi khi đặt vé: " << e.what() << endl;
        return;
    }

    saveTicketsToFile("../data/tickets.txt");
    seatService->saveSeatsToFile("../data/seats.txt");

    cout << "\nĐã thêm vé thành công!" << endl;
}

void TicketService::removeTicketFromKeyboard() {
    showAllTickets();

    string ticketId;
    cout << "Nhap ID ve can huy: ";
    cin >> ticketId;

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
        cout << "Khong tim thay ve voi ID: " << ticketId << endl;
        return;
    }

    seatService->cancelReservation(ticketToCancel.getSeat().getId());

    cancelTicket(ticketId);

    saveTicketsToFile("../data/tickets.txt");
    seatService->saveSeatsToFile("../data/seats.txt");

    cout << "\nĐa huy ve thanh cong!" << endl;
}