//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_MOVIE_H
#define BTLPHUC_MOVIE_H
#include <bits/stdc++.h>
#include "Ticket.h"

class Movie {
private:
    std::string id;
    std::string name;
    std::string genre;
    std::string director;
    std::string actors;
    int duration;
    std::string releaseDate;
    double rating;
    std::string description;

public:
    Movie();
    Movie(std::string id, std::string name, std::string genre, std::string director, std::string actors,
          int duration, std::string releaseDate, double rating, std::string description);

    std::string getId();
    std::string getName();
    std::string getGenre();
    std::string getDirector();
    std::string getActors();
    int getDuration();
    std::string getReleaseDate();
    double getRating();
    std::string getDescription();

    void setId(const std::string& newId);
    void setName(const std::string& newName);
    void setGenre(const std::string& newGenre);
    void setDirector(const std::string& newDirector);
    void setActors(const std::string& newActors);
    void setDuration(const int& newDuration);
    void setReleaseDate(const std::string& newReleaseDate);
    void setRating(const double& newRating);
    void setDescription(const std::string& newDescription);
};


#endif //BTLPHUC_MOVIE_H
