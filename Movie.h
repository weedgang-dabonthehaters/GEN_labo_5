//#include <utility>

// Movie.h
#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include "PriceCode.h"

class Movie {
public:
    explicit Movie( std::string  title, std::shared_ptr<PriceCode> priceCode );

    virtual std::shared_ptr<PriceCode> getPriceCode() const;
    virtual void setPriceCode( std::shared_ptr<PriceCode> arg );
    virtual std::string getTitle() const;

private:
    std::string _title;
    std::shared_ptr<PriceCode> _priceCode;
};

inline Movie::
Movie::Movie(std::string title, std::shared_ptr<PriceCode> priceCode)
        : _title(std::move( title )), _priceCode(std::move( priceCode ))
{}

inline std::shared_ptr<PriceCode> Movie::
getPriceCode() const { return _priceCode; }

inline void Movie::
setPriceCode( std::shared_ptr<PriceCode> arg ) { _priceCode = std::move(arg); }

inline std::string Movie::
getTitle() const { return _title; }

#endif // MOVIE_H