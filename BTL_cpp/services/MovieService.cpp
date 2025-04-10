//
// Created by admin on 4/24/2025.
//

#include "MovieService.h"
#include <bits/stdc++.h>


MovieService::MovieService() {}

void MovieService::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void MovieService::removeMovieFromKeyboard() {
    // Hien thi danh sach phim de nguoi dung co the xem ID
    showAllMovies();

    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                    XOA PHIM                               |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::string movieId;
    std::cout << "| Nhap ID phim can xoa: ";
    std::cin >> movieId;

    try {
        // Tim va xoa phim voi ID tuong ung
        removeMovie(movieId);

        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "|               DA XOA PHIM THANH CONG!                     |" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
    } catch (const std::runtime_error& e) {
        // Xu ly truong hop khong tim thay phim
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| Loi: " << std::left << std::setw(52) << e.what() << "|" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
    }

    // Luu danh sach phim da cap nhat vao file
    saveMoviesToFile("../data/movie.txt");

    // Xoa buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void MovieService::updateMovieFromKeyboard() {
    std::string movieId;

    // Hien thi danh sach phim de nguoi dung chon
    showAllMovies();

    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                    CAP NHAT THONG TIN PHIM                |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    // Yeu cau ID phim can cap nhat
    std::cout << "| Nhap ID phim can cap nhat: ";
    std::cin >> movieId;

    // Tim phim voi ID da nhap
    bool found = false;
    Movie currentMovie;

    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            currentMovie = movie;
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "| Khong tim thay phim voi ID: " << movieId << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        return;
    }

    // Hien thi thong tin phim hien tai
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                THONG TIN PHIM HIEN TAI                    |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "| ID: " << std::left << std::setw(53) << currentMovie.getId() << "|" << std::endl;
    std::cout << "| Ten: " << std::left << std::setw(52) << currentMovie.getName() << "|" << std::endl;
    std::cout << "| The loai: " << std::left << std::setw(47) << currentMovie.getGenre() << "|" << std::endl;
    std::cout << "| Dao dien: " << std::left << std::setw(47) << currentMovie.getDirector() << "|" << std::endl;
    std::cout << "| Dien vien: " << std::left << std::setw(46) << currentMovie.getActors() << "|" << std::endl;
    std::cout << "| Thoi luong: " << std::left << std::setw(45) << (std::to_string(currentMovie.getDuration()) + " phut") << "|" << std::endl;
    std::cout << "| Ngay phat hanh: " << std::left << std::setw(41) << currentMovie.getReleaseDate() << "|" << std::endl;
    std::cout << "| Danh gia: " << std::left << std::setw(46) << (std::to_string(currentMovie.getRating()) + "/10") << "|" << std::endl;
    std::cout << "| Mo ta: " << std::left << std::setw(49) << currentMovie.getDescription() << "|" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::cin.ignore(); // Xoa buffer

    std::cout << "|          NHAP THONG TIN MOI (DE TRONG DE GIU NGUYEN)      |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::string name, genre, director, actors, releaseDate, description;
    int duration;
    double rating;

    std::cout << "| Ten phim: ";
    std::getline(std::cin, name);
    if (name.empty()) name = currentMovie.getName();

    std::cout << "| The loai: ";
    std::getline(std::cin, genre);
    if (genre.empty()) genre = currentMovie.getGenre();

    std::cout << "| Dao dien: ";
    std::getline(std::cin, director);
    if (director.empty()) director = currentMovie.getDirector();

    std::cout << "| Dien vien: ";
    std::getline(std::cin, actors);
    if (actors.empty()) actors = currentMovie.getActors();

    std::cout << "| Thoi luong (phut): ";
    std::string durationStr;
    std::getline(std::cin, durationStr);
    if (durationStr.empty()) {
        duration = currentMovie.getDuration();
    } else {
        try {
            duration = std::stoi(durationStr);
        } catch (const std::exception& e) {
            std::cout << "| Loi: Thoi luong khong hop le. Giu nguyen gia tri cu." << std::endl;
            duration = currentMovie.getDuration();
        }
    }

    std::cout << "| Ngay phat hanh (YYYY-MM-DD): ";
    std::getline(std::cin, releaseDate);
    if (releaseDate.empty()) releaseDate = currentMovie.getReleaseDate();

    std::cout << "| Danh gia (1.0-10.0): ";
    std::string ratingStr;
    std::getline(std::cin, ratingStr);
    if (ratingStr.empty()) {
        rating = currentMovie.getRating();
    } else {
        try {
            rating = std::stod(ratingStr);
            if (rating < 0 || rating > 10) {
                std::cout << "| Loi: Danh gia phai tu 0 den 10. Giu nguyen gia tri cu." << std::endl;
                rating = currentMovie.getRating();
            }
        } catch (const std::exception& e) {
            std::cout << "| Loi: Danh gia khong hop le. Giu nguyen gia tri cu." << std::endl;
            rating = currentMovie.getRating();
        }
    }

    std::cout << "| Mo ta: ";
    std::getline(std::cin, description);
    if (description.empty()) description = currentMovie.getDescription();

    // Tao doi tuong Movie moi voi thong tin da cap nhat
    Movie updatedMovie(movieId, name, genre, director, actors, duration, releaseDate, rating, description);

    // Cap nhat phim
    updateMovie(movieId, updatedMovie);
    saveMoviesToFile("../data/movie.txt");

    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|              CAP NHAT PHIM THANH CONG!                    |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
}


void MovieService::addMovieFromKeyboard() {
    std::string id, name, genre, director, actors, releaseDate, description;
    int duration;
    double rating;

    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|                    NHAP THONG TIN PHIM                    |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;

    std::cout << "| ID phim: ";
    std::cin >> id;

    Movie check = getMovieById(id); // Kiem tra ID phim da ton tai hay chua
    if (check.getId() != "-1") {
        std::cout << "| Loi: ID phim da ton tai. Vui long nhap ID khac." << std::endl;
        return;
    }

    std::cin.ignore(); // Loai bo ky tu newline trong buffer

    std::cout << "| Ten phim: ";
    std::getline(std::cin, name);

    std::cout << "| The loai: ";
    std::getline(std::cin, genre);

    std::cout << "| Dao dien: ";
    std::getline(std::cin, director);

    std::cout << "| Dien vien: ";
    std::getline(std::cin, actors);

    std::cout << "| Thoi luong (phut): ";
    std::cin >> duration;

    std::cin.ignore(); // Loai bo ky tu newline trong buffer

    std::cout << "| Ngay phat hanh (YYYY-MM-DD): ";
    std::getline(std::cin, releaseDate);

    std::cout << "| Danh gia (1.0-10.0): ";
    std::cin >> rating;

    std::cin.ignore(); // Loai bo ky tu newline trong buffer

    std::cout << "| Mo ta: ";
    std::getline(std::cin, description);

    // Tao doi tuong Movie moi va them vao danh sach
    Movie newMovie(id, name, genre, director, actors, duration, releaseDate, rating, description);
    addMovie(newMovie);
    saveMoviesToFile("../data/movie.txt");

    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "|               DA THEM PHIM THANH CONG!                    |" << std::endl;
    std::cout << "+-----------------------------------------------------------+" << std::endl;
}

void MovieService::removeMovie(const std::string& movieId) {
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (it->getId() == movieId) {
            movies.erase(it);
            return;
        }
    }
    throw std::runtime_error("Movie not found");
}

Movie MovieService::getMovieById(const std::string& movieId) {
    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            return movie;
        }
    }
    Movie movie;
    movie.setId("-1");
    throw std::runtime_error("Movie not found: " + movieId);
    return movie;
}

std::vector<Movie> MovieService::getAllMovies() {
    return movies;
}

void MovieService::updateMovie(const std::string& movieId, Movie& updatedMovie) {
    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            movie = updatedMovie;
            return;
        }
    }
}

void MovieService::loadMoviesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    movies.clear();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string id, name, genre, director, actors, releaseDate, description;
        std::string durationStr, ratingStr;

        std::getline(iss, id, ',');
        std::getline(iss, name, ',');
        std::getline(iss, genre, ',');
        std::getline(iss, director, ',');
        std::getline(iss, actors, ',');
        std::getline(iss, durationStr, ',');
        std::getline(iss, releaseDate, ',');
        std::getline(iss, ratingStr, ',');
        std::getline(iss, description);

        int duration = std::stoi(durationStr);
        double rating = std::stod(ratingStr);

        movies.push_back(Movie(id, name, genre, director, actors, duration, releaseDate, rating, description));
    }

    file.close();
}

void MovieService::saveMoviesToFile(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    for (auto& movie : movies) {
        file << movie.getId() << ","
             << movie.getName() << ","
             << movie.getGenre() << ","
             << movie.getDirector() << ","
             << movie.getActors() << ","
             << movie.getDuration() << ","
             << movie.getReleaseDate() << ","
             << movie.getRating() << ","
             << movie.getDescription() << "\n";
    }

    file.close();
}

void MovieService::showAllMovies() {
    if (movies.empty()) {
        std::cout << "\n=== DANH SACH PHIM TRONG ===\n" << std::endl;
        return;
    }

    std::cout << "\n==================== DANH SACH PHIM ====================\n" << std::endl;

    for (auto& movie : movies) {
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| ID phim: " << std::left << std::setw(53) << movie.getId() << "|" << std::endl;
        std::cout << "|-----------------------------------------------------------|" << std::endl;
        std::cout << "| Ten phim:      " << std::left << std::setw(46) << movie.getName() << "|" << std::endl;
        std::cout << "| The loai:      " << std::left << std::setw(46) << movie.getGenre() << "|" << std::endl;
        std::cout << "| Dao dien:      " << std::left << std::setw(46) << movie.getDirector() << "|" << std::endl;
        std::cout << "| Dien vien:     " << std::left << std::setw(46) << movie.getActors() << "|" << std::endl;
        std::cout << "| Thoi luong:    " << std::left << std::setw(46) << (std::to_string(movie.getDuration()) + " phut") << "|" << std::endl;
        std::cout << "| Ngay ra mat:   " << std::left << std::setw(46) << movie.getReleaseDate() << "|" << std::endl;
        std::cout << "| Danh gia:      " << std::left << std::setw(46) << (std::to_string(movie.getRating()) + "/10") << "|" << std::endl;
        std::cout << "|-----------------------------------------------------------|" << std::endl;
        std::cout << "| Mo ta:                                                    |" << std::endl;

        // Xử lý mô tả dài, tách thành nhiều dòng nếu cần
        std::string description = movie.getDescription();
        int maxWidth = 57;
        for (size_t i = 0; i < description.length(); i += maxWidth) {
            std::string line = description.substr(i, maxWidth);
            std::cout << "| " << std::left << std::setw(57) << line << "|" << std::endl;
        }

        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << std::endl;
    }

    std::cout << "====================== KET THUC ======================" << std::endl;
}


