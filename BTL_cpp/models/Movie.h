//
// Created by admin on 4/24/2025.
//

#ifndef BTLPHUC_MOVIE_H
#define BTLPHUC_MOVIE_H
#include <bits/stdc++.h>
#include "Ticket.h"

using namespace std;

class Movie {
private:
    string id;
    string name;
    string genre;
    string director;
    string actors;
    int duration;
    string releaseDate;
    double rating;
    string description;

public:
    Movie();
    Movie(string id, string name, string genre, string director, string actors,
          int duration, string releaseDate, double rating, string description);

    string getId();
    string getName();
    string getGenre();
    string getDirector();
    string getActors();
    int getDuration();
    string getReleaseDate();
    double getRating();
    string getDescription();

    void setId(const string& newId);
    void setName(const string& newName);
    void setGenre(const string& newGenre);
    void setDirector(const string& newDirector);
    void setActors(const string& newActors);
    void setDuration(const int& newDuration);
    void setReleaseDate(const string& newReleaseDate);
    void setRating(const double& newRating);
    void setDescription(const string& newDescription);
};

#endif //BTLPHUC_MOVIE_H