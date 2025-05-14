#include "MovieService.h"
#include <bits/stdc++.h>

using namespace std;

MovieService::MovieService() {}

void MovieService::addMovie(const Movie& movie) {
    movies.push_back(movie);
}

void MovieService::removeMovieFromKeyboard() {
    showAllMovies();

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                    XOA PHIM                               |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    string movieId;
    cout << "| Nhap ID phim can xoa: ";
    cin >> movieId;

    try {
        removeMovie(movieId);

        cout << "+-----------------------------------------------------------+" << endl;
        cout << "|               DA XOA PHIM THANH CONG!                     |" << endl;
        cout << "+-----------------------------------------------------------+" << endl;
    } catch (const runtime_error& e) {
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "| Loi: " << left << setw(52) << e.what() << "|" << endl;
        cout << "+-----------------------------------------------------------+" << endl;
    }

    saveMoviesToFile("../data/movie.txt");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void MovieService::updateMovieFromKeyboard() {
    string movieId;

    showAllMovies();

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                    CAP NHAT THONG TIN PHIM                |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    cout << "| Nhap ID phim can cap nhat: ";
    cin >> movieId;

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
        cout << "| Khong tim thay phim voi ID: " << movieId << endl;
        cout << "+-----------------------------------------------------------+" << endl;
        return;
    }

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                THONG TIN PHIM HIEN TAI                    |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
    cout << "| ID: " << left << setw(53) << currentMovie.getId() << "|" << endl;
    cout << "| Ten: " << left << setw(52) << currentMovie.getName() << "|" << endl;
    cout << "| The loai: " << left << setw(47) << currentMovie.getGenre() << "|" << endl;
    cout << "| Dao dien: " << left << setw(47) << currentMovie.getDirector() << "|" << endl;
    cout << "| Dien vien: " << left << setw(46) << currentMovie.getActors() << "|" << endl;
    cout << "| Thoi luong: " << left << setw(45) << (to_string(currentMovie.getDuration()) + " phut") << "|" << endl;
    cout << "| Ngay phat hanh: " << left << setw(41) << currentMovie.getReleaseDate() << "|" << endl;
    cout << "| Danh gia: " << left << setw(46) << (to_string(currentMovie.getRating()) + "/10") << "|" << endl;
    cout << "| Mo ta: " << left << setw(49) << currentMovie.getDescription() << "|" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    cin.ignore();

    cout << "|                    NHAP THONG TIN MOI                     |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    string name, genre, director, actors, releaseDate, description;
    int duration;
    double rating;

    cout << "| Ten phim: ";
    getline(cin, name);
    if (name.empty()) name = currentMovie.getName();

    cout << "| The loai: ";
    getline(cin, genre);
    if (genre.empty()) genre = currentMovie.getGenre();

    cout << "| Dao dien: ";
    getline(cin, director);
    if (director.empty()) director = currentMovie.getDirector();

    cout << "| Dien vien: ";
    getline(cin, actors);
    if (actors.empty()) actors = currentMovie.getActors();

    cout << "| Thoi luong (phut): ";
    string durationStr;
    getline(cin, durationStr);
    if (durationStr.empty()) {
        duration = currentMovie.getDuration();
    } else {
        try {
            duration = stoi(durationStr);
        } catch (const exception& e) {
            cout << "| Loi: Thoi luong khong hop le. Giu nguyen gia tri cu." << endl;
            duration = currentMovie.getDuration();
        }
    }

    cout << "| Ngay phat hanh (YYYY-MM-DD): ";
    getline(cin, releaseDate);
    if (releaseDate.empty()) releaseDate = currentMovie.getReleaseDate();

    cout << "| Danh gia (1.0-10.0): ";
    string ratingStr;
    getline(cin, ratingStr);
    if (ratingStr.empty()) {
        rating = currentMovie.getRating();
    } else {
        try {
            rating = stod(ratingStr);
            if (rating < 0 || rating > 10) {
                cout << "| Loi: Danh gia phai tu 0 den 10. Giu nguyen gia tri cu." << endl;
                rating = currentMovie.getRating();
            }
        } catch (const exception& e) {
            cout << "| Loi: Danh gia khong hop le. Giu nguyen gia tri cu." << endl;
            rating = currentMovie.getRating();
        }
    }

    cout << "| Mo ta: ";
    getline(cin, description);
    if (description.empty()) description = currentMovie.getDescription();

    Movie updatedMovie(movieId, name, genre, director, actors, duration, releaseDate, rating, description);

    updateMovie(movieId, updatedMovie);
    saveMoviesToFile("../data/movie.txt");

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|              CAP NHAT PHIM THANH CONG!                    |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
}

void MovieService::addMovieFromKeyboard() {
    string id, name, genre, director, actors, releaseDate, description;
    int duration;
    double rating;

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|                    NHAP THONG TIN PHIM                    |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;

    cout << "| ID phim: ";
    cin >> id;

    Movie check = getMovieById(id);
    if (check.getId() != "-1") {
        cout << "| Loi: ID phim da ton tai. Vui long nhap ID khac." << endl;
        return;
    }

    cin.ignore();

    cout << "| Ten phim: ";
    getline(cin, name);

    cout << "| The loai: ";
    getline(cin, genre);

    cout << "| Dao dien: ";
    getline(cin, director);

    cout << "| Dien vien: ";
    getline(cin, actors);

    cout << "| Thoi luong (phut): ";
    cin >> duration;

    cin.ignore();

    cout << "| Ngay phat hanh (YYYY-MM-DD): ";
    getline(cin, releaseDate);

    cout << "| Danh gia (1.0-10.0): ";
    cin >> rating;

    cin.ignore();

    cout << "| Mo ta: ";
    getline(cin, description);

    Movie newMovie(id, name, genre, director, actors, duration, releaseDate, rating, description);
    addMovie(newMovie);
    saveMoviesToFile("../data/movie.txt");

    cout << "+-----------------------------------------------------------+" << endl;
    cout << "|               DA THEM PHIM THANH CONG!                    |" << endl;
    cout << "+-----------------------------------------------------------+" << endl;
}

void MovieService::removeMovie(const string& movieId) {
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (it->getId() == movieId) {
            movies.erase(it);
            return;
        }
    }
    throw runtime_error("Movie not found");
}

Movie MovieService::getMovieById(const string& movieId) {
    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            return movie;
        }
    }
    Movie movie;
    movie.setId("-1");
    return movie;
}

vector<Movie> MovieService::getAllMovies() {
    return movies;
}

void MovieService::updateMovie(const string& movieId, Movie& updatedMovie) {
    for (auto& movie : movies) {
        if (movie.getId() == movieId) {
            movie = updatedMovie;
            return;
        }
    }
}

void MovieService::loadMoviesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    movies.clear();
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string id, name, genre, director, actors, releaseDate, description;
        string durationStr, ratingStr;

        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, genre, ',');
        getline(iss, director, ',');
        getline(iss, actors, ',');
        getline(iss, durationStr, ',');
        getline(iss, releaseDate, ',');
        getline(iss, ratingStr, ',');
        getline(iss, description);

        int duration = stoi(durationStr);
        double rating = stod(ratingStr);

        movies.push_back(Movie(id, name, genre, director, actors, duration, releaseDate, rating, description));
    }

    file.close();
}

void MovieService::saveMoviesToFile(const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file");
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
        cout << "\n=== DANH SACH PHIM TRONG ===\n" << endl;
        return;
    }

    cout << "\n==================== DANH SACH PHIM ====================\n" << endl;

    for (auto& movie : movies) {
        cout << "+-----------------------------------------------------------+" << endl;
        cout << "| ID phim: " << left << setw(53) << movie.getId() << "|" << endl;
        cout << "|-----------------------------------------------------------|" << endl;
        cout << "| Ten phim:      " << left << setw(46) << movie.getName() << "|" << endl;
        cout << "| The loai:      " << left << setw(46) << movie.getGenre() << "|" << endl;
        cout << "| Dao dien:      " << left << setw(46) << movie.getDirector() << "|" << endl;
        cout << "| Dien vien:     " << left << setw(46) << movie.getActors() << "|" << endl;
        cout << "| Thoi luong:    " << left << setw(46) << (to_string(movie.getDuration()) + " phut") << "|" << endl;
        cout << "| Ngay ra mat:   " << left << setw(46) << movie.getReleaseDate() << "|" << endl;
        cout << "| Danh gia:      " << left << setw(46) << (to_string(movie.getRating()) + "/10") << "|" << endl;
        cout << "|-----------------------------------------------------------|" << endl;
        cout << "| Mo ta:                                                    |" << endl;

        string description = movie.getDescription();
        int maxWidth = 57;
        for (size_t i = 0; i < description.length(); i += maxWidth) {
            string line = description.substr(i, maxWidth);
            cout << "| " << left << setw(57) << line << "|" << endl;
        }

        cout << "+-----------------------------------------------------------+" << endl;
        cout << endl;
    }

    cout << "====================== KET THUC ======================" << endl;
}
