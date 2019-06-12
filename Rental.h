#include <utility>

#include <utility>

// Rental.h
#ifndef RENTAL_H
#define RENTAL_H
#include "Movie.h"

class Rental {
public:
    Rental( std::shared_ptr<Movie> movie, int daysRented );

    Rental(std::shared_ptr<Movie> movie);

    int getDaysRented() const;
    const std::shared_ptr<Movie> getMovie() const;

private:
    const std::shared_ptr<Movie> _movie;
    int _daysRented;
};

inline Rental::
Rental( std::shared_ptr<Movie> movie, int daysRented )
        : _movie(std::move( movie ))
        , _daysRented( daysRented ) {}

inline int Rental::
getDaysRented() const { return _daysRented; }

inline const std::shared_ptr<Movie> Rental::
getMovie() const { return _movie; }

Rental::Rental(std::shared_ptr<Movie> movie) : _movie(std::move(movie)) {}

#endif // RENTAL_H