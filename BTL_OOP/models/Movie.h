#ifndef MOVIE_H
#define MOVIE_H

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
    void setDuration(int newDuration);
    void setReleaseDate(const string& newReleaseDate);
    void setRating(double newRating);
    void setDescription(const string& newDescription);
};

#endif //MOVIE_H