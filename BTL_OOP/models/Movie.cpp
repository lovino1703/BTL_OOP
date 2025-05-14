#include "Movie.h"
#include <bits/stdc++.h>

using namespace std;

Movie::Movie() : id(""), name(""), genre(""), director(""), actors(""),
                duration(0), releaseDate(""), rating(0.0), description("") {}

Movie::Movie(string id, string name, string genre, string director, string actors,
             int duration, string releaseDate, double rating, string description)
    : id(id), name(name), genre(genre), director(director), actors(actors),
      duration(duration), releaseDate(releaseDate), rating(rating), description(description) {}

string Movie::getId() { return id; }
string Movie::getName() { return name; }
string Movie::getGenre() { return genre; }
string Movie::getDirector() { return director; }
string Movie::getActors() { return actors; }
int Movie::getDuration() { return duration; }
string Movie::getReleaseDate() { return releaseDate; }
double Movie::getRating() { return rating; }
string Movie::getDescription() { return description; }

void Movie::setId(const string& newId) { id = newId; }
void Movie::setName(const string& newName) { name = newName; }
void Movie::setGenre(const string& newGenre) { genre = newGenre; }
void Movie::setDirector(const string& newDirector) { director = newDirector; }
void Movie::setActors(const string& newActors) { actors = newActors; }
void Movie::setDuration(int newDuration) { duration = newDuration; }
void Movie::setReleaseDate(const string& newReleaseDate) { releaseDate = newReleaseDate; }
void Movie::setRating(double newRating) { rating = newRating; }
void Movie::setDescription(const string& newDescription) { description = newDescription; }