#include "SeatService.h"
#include <bits/stdc++.h>
#include "../models/Seat.h"

using namespace std;

SeatService::SeatService() {
    // Constructor implementation
}

void SeatService::addSeat(const Seat& seat) {
    seats.push_back(seat);
}

void SeatService::reserveSeat(const string& seatId, const string &showtimes, const string &movieId) {
    for (auto& seat : seats) {
        if (seat.getId() == seatId && seat.getIsAvailable() && seat.getShowtimeId() == showtimes && seat.getMovieId() == movieId){
            seat.setIsAvailable(false);
            cout << "Seat " << seatId << " reserved successfully." << endl;
            return;
        }
    }
    cout << "Seat " << seatId << " is not available." << endl;
}

void SeatService::cancelReservation(const string& seatId) {
    for (auto& seat : seats) {
        if (seat.getId() == seatId && !seat.getIsAvailable()) {
            seat.setIsAvailable(true);
            cout << "Reservation for seat " << seatId << " cancelled successfully." << endl;
            return;
        }
    }
    cout << "Seat " << seatId << " is not reserved." << endl;
}

vector<Seat> SeatService::getAllSeats() {
    return seats;
}

void SeatService::loadSeatsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Error creating file: " << filename << endl;
            return;
        }
        outFile.close();
        return;
    }

    seats.clear();
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string id, priceStr, seatId, movieId, showtimeId, availableStr;

        getline(iss, id, ',');
        getline(iss, priceStr, ',');
        getline(iss, seatId, ',');
        getline(iss, movieId, ',');
        getline(iss, showtimeId, ',');
        getline(iss, availableStr);

        bool isAvailable = (availableStr == "true");

        seats.push_back(Seat(movieId, seatId, showtimeId, isAvailable));
    }

    file.close();
}

void SeatService::saveSeatsToFile(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& seat : seats) {
        file << "S" + seat.getId() << ","
             << "0" << ","
             << seat.getId() << ","
             << seat.getMovieId() << ","
             << seat.getShowtimeId() << ","
             << (seat.getIsAvailable() ? "true" : "false") << "\n";
    }

    file.close();
    cout << "Seats data saved to " << filename << " successfully." << endl;
}

void SeatService::addSeatFromKeyboard() {
    string movieId, seatId, showtimeId;
    bool isAvailable;

    cout << "\nNhap ID phim (vi du: M001): ";
    cin >> movieId;

    cout << "Nhap ID ghe (vi du: A1, B2): ";
    cin >> seatId;

    cout << "Nhap ID suat chieu (vi du: ST001): ";
    cin >> showtimeId;

    isAvailable = true;

    for (const auto& seat : seats) {
        if (seat.getId() == seatId && seat.getMovieId() == movieId && seat.getShowtimeId() == showtimeId) {
            cout << "Ghe nay da ton tai cho phim va suat chieu nay!" << endl;
            return;
        }
    }

    Seat newSeat(movieId, seatId, showtimeId, isAvailable);
    seats.push_back(newSeat);

    saveSeatsToFile("../data/seats.txt");

    cout << "Them ghe thanh cong!" << endl;
}

void SeatService::removeSeatFromKeyboard() {
    showAllSeats();

    string movieId, seatId, showtimeId;

    cout << "\nNhap thong tin ghe can xoa:" << endl;
    cout << "ID phim: ";
    cin >> movieId;

    cout << "ID ghe: ";
    cin >> seatId;

    cout << "ID suat chieu: ";
    cin >> showtimeId;

    for (auto it = seats.begin(); it != seats.end(); ++it) {
        if (it->getId() == seatId && it->getMovieId() == movieId && it->getShowtimeId() == showtimeId) {
            seats.erase(it);

            saveSeatsToFile("../data/seats.txt");

            cout << "Xoa ghe thanh cong!" << endl;
            return;
        }
    }

    cout << "Khong tim thay ghe voi thong tin da nhap!" << endl;
}

void SeatService::showAllSeats() {
    if (seats.empty()) {
        cout << "\n=== DANH SACH GHE TRONG ===\n" << endl;
        return;
    }

    cout << "\n==================== DANH SACH GHE ====================\n" << endl;

    map<string, map<string, vector<Seat>>> seatsByMovieAndShowtime;

    for (const auto& seat : seats) {
        seatsByMovieAndShowtime[seat.getMovieId()][seat.getShowtimeId()].push_back(seat);
    }

    for (const auto& moviePair : seatsByMovieAndShowtime) {
        cout << "Phim: " << moviePair.first << endl;

        for (const auto& showtimePair : moviePair.second) {
            cout << "  Suat chieu: " << showtimePair.first << endl;
            cout << "  +-------------------------------------------+" << endl;
            cout << "  |                MAN HINH                   |" << endl;
            cout << "  +-------------------------------------------+" << endl;

            map<char, map<int, bool>> seatMatrix;

            for (const auto& seat : showtimePair.second) {
                char row = seat.getId()[0];
                int column = 0;

                try {
                    column = stoi(seat.getId().substr(1));
                } catch (const exception& e) {
                    continue;
                }

                seatMatrix[row][column] = seat.getIsAvailable();
            }

            for (char row = 'A'; row <= 'E'; row++) {
                cout << "  " << row << " | ";
                for (int col = 1; col <= 5; col++) {
                    bool found = false;
                    bool available = true;

                    if (seatMatrix.count(row) > 0 && seatMatrix[row].count(col) > 0) {
                        found = true;
                        available = seatMatrix[row][col];
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

            cout << "  +-------------------------------------------+" << endl;
            cout << "  Chu thich: O = Ghe trong, X = Ghe da dat, - = Khong co ghe\n" << endl;
        }
        cout << endl;
    }

    cout << "====================== KET THUC ======================" << endl;
}

void SeatService::resetSeats() {
    char confirm;
    cout << "Ban co chac chan muon dat lai tat ca cac ghe ve trang thai trong? (y/n): ";
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "Huy bo thao tac dat lai ghe." << endl;
        return;
    }

    for (auto& seat : seats) {
        seat.setIsAvailable(true);
    }

    saveSeatsToFile("../data/seats.txt");

    cout << "Da dat lai tat ca cac ghe ve trang thai trong!" << endl;
}
