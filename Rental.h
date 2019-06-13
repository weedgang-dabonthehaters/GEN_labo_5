#include <utility>

#include <utility>

// Rental.h
#ifndef RENTAL_H
#define RENTAL_H
#include "Movie.h"

class Rental {
public:
    Rental( std::shared_ptr<Movie> movie, const int& daysRented );

    Rental(std::shared_ptr<Movie> movie);

    virtual int getDaysRented() const;
    virtual std::shared_ptr<Movie> getMovie() const;
    virtual double getRentalAmount() const;
    friend std::ostream &operator<<( std::ostream &output, const Rental &r );
    virtual std::string getInfo();

private:
    std::shared_ptr<Movie> _movie;
    int _daysRented;
};

inline Rental::
Rental( std::shared_ptr<Movie> movie, const int& daysRented )
        : _movie(std::move( movie ))
        , _daysRented( daysRented ) {}

inline int Rental::
getDaysRented() const { return _daysRented; }

inline std::shared_ptr<Movie> Rental::
getMovie() const { return _movie; }

Rental::Rental(std::shared_ptr<Movie> movie) : _movie(std::move(movie)) {}

double Rental::getRentalAmount() const {
    return _movie->getPriceCode()->getAmount(_daysRented);
}

std::ostream &operator<<(std::ostream &output, const Rental &r) {
    output << "\t" << r.getMovie()->getTitle() << "\t"
           << r.getRentalAmount() << "\n";
    return output;
}

std::string Rental::getInfo() {
    std::ostringstream output;
    output << "\t" << getMovie()->getTitle() << "\t"
           << getRentalAmount() << "\n";
    return output.str();
}

#endif // RENTAL_H