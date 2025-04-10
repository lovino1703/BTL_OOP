//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_MOVIESERVICE_H
#define BTLPHUC_MOVIESERVICE_H
#include <bits/stdc++.h>
#include "../models/Movie.h"


class MovieService {
private:
    std::vector<Movie> movies;
public:
    MovieService();
    void addMovie(const Movie& movie);
    void addMovieFromKeyboard();
    void updateMovieFromKeyboard();
    void removeMovieFromKeyboard();
    void removeMovie(const std::string& movieId);
    Movie getMovieById(const std::string& movieId);
    std::vector<Movie> getAllMovies();
    void updateMovie(const std::string& movieId, Movie& updatedMovie);
    void loadMoviesFromFile(const std::string& filename);
    void saveMoviesToFile(const std::string& filename);
    void showAllMovies();
};


#endif //BTLPHUC_MOVIESERVICE_H
