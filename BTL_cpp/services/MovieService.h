//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_MOVIESERVICE_H
#define BTLPHUC_MOVIESERVICE_H
#include <bits/stdc++.h>
#include "../models/Movie.h"

using namespace std;

class MovieService {
private:
    vector<Movie> movies;
public:
    MovieService();
    void addMovie(const Movie& movie);
    void addMovieFromKeyboard();
    void updateMovieFromKeyboard();
    void removeMovieFromKeyboard();
    void removeMovie(const string& movieId);
    Movie getMovieById(const string& movieId);
    vector<Movie> getAllMovies();
    void updateMovie(const string& movieId, Movie& updatedMovie);
    void loadMoviesFromFile(const string& filename);
    void saveMoviesToFile(const string& filename);
    void showAllMovies();
    Movie checkMovieById(const string& movieId);
};


#endif //BTLPHUC_MOVIESERVICE_H