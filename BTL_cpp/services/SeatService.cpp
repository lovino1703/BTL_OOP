//
// Created by admin on 4/24/2025.
//

#include "SeatService.h"
#include <bits/stdc++.h>
#include "../models/Seat.h"

SeatService::SeatService() {
    // Constructor implementation
}

void SeatService::addSeat(const Seat& seat) {
    seats.push_back(seat);
}

void SeatService::reserveSeat(const std::string& seatId) {
    for (auto& seat : seats) {
        if (seat.getId() == seatId && seat.getIsAvailable()) {
            seat.setIsAvailable(false);
            std::cout << "Seat " << seatId << " reserved successfully." << std::endl;
            return;
        }
    }
    std::cout << "Seat " << seatId << " is not available." << std::endl;
}

void SeatService::cancelReservation(const std::string& seatId) {
    for (auto& seat : seats) {
        if (seat.getId() == seatId && !seat.getIsAvailable()) {
            seat.setIsAvailable(true);
            std::cout << "Reservation for seat " << seatId << " cancelled successfully." << std::endl;
            return;
        }
    }
    std::cout << "Seat " << seatId << " is not reserved." << std::endl;
}

std::vector<Seat> SeatService::getAllSeats() {
    return seats;
}

void SeatService::loadSeatsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Tạo file nếu không tồn tại
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error creating file: " << filename << std::endl;
            return;
        }
        outFile.close();
        return;
    }

    seats.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string id, priceStr, seatId, movieId, showtimeId, availableStr;

        std::getline(iss, id, ',');
        std::getline(iss, priceStr, ',');
        std::getline(iss, seatId, ',');
        std::getline(iss, movieId, ',');
        std::getline(iss, showtimeId, ',');
        std::getline(iss, availableStr);

        bool isAvailable = (availableStr == "true");

        seats.push_back(Seat(movieId, seatId, showtimeId, isAvailable));
    }

    file.close();
}

void SeatService::saveSeatsToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& seat : seats) {
        // Format: id,price,seatId,movieId,showtimeId,isAvailable
        file << "S" + seat.getId() << "," // ID ghế (tiền tố S + seatId)
             << "0" << ","
             << seat.getId() << "," // ID hiển thị của ghế (A1, B2, v.v.)
             << seat.getMovieId() << "," // ID phim
             << seat.getShowtimeId() << "," // ID suất chiếu
             << (seat.getIsAvailable() ? "true" : "false") << "\n"; // Trạng thái ghế
    }

    file.close();
    std::cout << "Seats data saved to " << filename << " successfully." << std::endl;
}

void SeatService::addSeatFromKeyboard() {
    std::string movieId, seatId, showtimeId;
    bool isAvailable;

    // Hiển thị danh sách phim để người dùng chọn
    std::cout << "\nNhap ID phim (vi du: M001): ";
    std::cin >> movieId;

    std::cout << "Nhap ID ghe (vi du: A1, B2): ";
    std::cin >> seatId;

    std::cout << "Nhap ID suat chieu (vi du: ST001): ";
    std::cin >> showtimeId;

    isAvailable = true;

    // Kiểm tra xem ghế đã tồn tại chưa
    for (const auto& seat : seats) {
        if (seat.getId() == seatId && seat.getMovieId() == movieId && seat.getShowtimeId() == showtimeId) {
            std::cout << "Ghe nay da ton tai cho phim va suat chieu nay!" << std::endl;
            return;
        }
    }

    // Tạo và thêm ghế mới
    Seat newSeat(movieId, seatId, showtimeId, isAvailable);
    seats.push_back(newSeat);

    // Lưu vào file
    saveSeatsToFile("../data/seats.txt");

    std::cout << "Them ghe thanh cong!" << std::endl;
}

void SeatService::removeSeatFromKeyboard() {
    // Hiển thị danh sách ghế để người dùng chọn
    showAllSeats();

    std::string movieId, seatId, showtimeId;

    std::cout << "\nNhap thong tin ghe can xoa:" << std::endl;
    std::cout << "ID phim: ";
    std::cin >> movieId;

    std::cout << "ID ghe: ";
    std::cin >> seatId;

    std::cout << "ID suat chieu: ";
    std::cin >> showtimeId;

    // Tìm và xóa ghế
    for (auto it = seats.begin(); it != seats.end(); ++it) {
        if (it->getId() == seatId && it->getMovieId() == movieId && it->getShowtimeId() == showtimeId) {
            seats.erase(it);

            // Lưu vào file
            saveSeatsToFile("../data/seats.txt");

            std::cout << "Xoa ghe thanh cong!" << std::endl;
            return;
        }
    }

    std::cout << "Khong tim thay ghe voi thong tin da nhap!" << std::endl;
}

void SeatService::showAllSeats() {
    if (seats.empty()) {
        std::cout << "\n=== DANH SACH GHE TRONG ===\n" << std::endl;
        return;
    }

    std::cout << "\n==================== DANH SACH GHE ====================\n" << std::endl;

    // Sắp xếp ghế theo phim và suất chiếu để dễ xem
    std::map<std::string, std::map<std::string, std::vector<Seat>>> seatsByMovieAndShowtime;

    for (const auto& seat : seats) {
        seatsByMovieAndShowtime[seat.getMovieId()][seat.getShowtimeId()].push_back(seat);
    }

    for (const auto& moviePair : seatsByMovieAndShowtime) {
        std::cout << "Phim: " << moviePair.first << std::endl;

        for (const auto& showtimePair : moviePair.second) {
            std::cout << "  Suat chieu: " << showtimePair.first << std::endl;
            std::cout << "  +-------------------------------------------+" << std::endl;
            std::cout << "  |                MAN HINH                   |" << std::endl;
            std::cout << "  +-------------------------------------------+" << std::endl;

            // Tạo ma trận ghế để hiển thị
            std::map<char, std::map<int, bool>> seatMatrix; // Hàng, Cột, Trạng thái

            for (const auto& seat : showtimePair.second) {
                // Phân tách ID ghế thành hàng và cột
                char row = seat.getId()[0]; // Ký tự đầu tiên là hàng (A, B, C, ...)
                int column = 0;

                // Chuyển đổi phần số trong ID ghế thành số nguyên
                try {
                    column = std::stoi(seat.getId().substr(1));
                } catch (const std::exception& e) {
                    continue; // Bỏ qua ghế có định dạng không hợp lệ
                }

                seatMatrix[row][column] = seat.getIsAvailable();
            }

            // Hiển thị ma trận ghế
            for (char row = 'A'; row <= 'E'; row++) {
                std::cout << "  " << row << " | ";
                for (int col = 1; col <= 5; col++) {
                    bool found = false;
                    bool available = true;

                    if (seatMatrix.count(row) > 0 && seatMatrix[row].count(col) > 0) {
                        found = true;
                        available = seatMatrix[row][col];
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

            std::cout << "  +-------------------------------------------+" << std::endl;
            std::cout << "  Chu thich: O = Ghe trong, X = Ghe da dat, - = Khong co ghe\n" << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "====================== KET THUC ======================" << std::endl;
}

void SeatService::resetSeats() {
    char confirm;
    std::cout << "Ban co chac chan muon dat lai tat ca cac ghe ve trang thai trong? (y/n): ";
    std::cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "Huy bo thao tac dat lai ghe." << std::endl;
        return;
    }

    // Đặt lại tất cả các ghế về trạng thái trống
    for (auto& seat : seats) {
        seat.setIsAvailable(true);
    }

    // Lưu vào file
    saveSeatsToFile("../data/seats.txt");

    std::cout << "Da dat lai tat ca cac ghe ve trang thai trong!" << std::endl;
}


