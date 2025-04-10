//
// Created by admin on 4/24/2025.
//

#include "Movie.h"
#include <bits/stdc++.h>

Movie::Movie() : id(""), name(""), duration(0), genre(""), releaseDate(""), description("") {}

Movie::Movie(std::string id, std::string name, std::string genre, std::string director, std::string actors,
             int duration, std::string releaseDate, double rating, std::string description)
        : id(id), name(name), genre(genre), director(director), actors(actors),
          duration(duration), releaseDate(releaseDate), rating(rating), description(description) {

}

std::string Movie::getId() {
    return id;
}

std::string Movie::getName() {
    return name;
}

std::string Movie::getGenre() {
    return genre;
}

std::string Movie::getDirector() {
    return director;
}

std::string Movie::getActors() {
    return actors;
}

int Movie::getDuration() {
    return duration;
}

std::string Movie::getReleaseDate() {
    return releaseDate;
}

double Movie::getRating() {
    return rating;
}

std::string Movie::getDescription() {
    return description;
}

void Movie::setId(const std::string& newId) {
    id = newId;
}

void Movie::setName(const std::string& newName) {
    name = newName;
}

void Movie::setGenre(const std::string& newGenre) {
    genre = newGenre;
}

void Movie::setDirector(const std::string& newDirector) {
    director = newDirector;
}

void Movie::setActors(const std::string& newActors) {
    actors = newActors;
}

void Movie::setDuration(const int& newDuration) {
    duration = newDuration;
}

void Movie::setReleaseDate(const std::string& newReleaseDate) {
    releaseDate = newReleaseDate;
}

void Movie::setRating(const double& newRating) {
    rating = newRating;
}

void Movie::setDescription(const std::string& newDescription) {
    description = newDescription;
}