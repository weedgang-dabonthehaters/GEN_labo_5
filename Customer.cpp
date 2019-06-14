#include <utility>

// Customer.cpp
#include <sstream>
#include <vector>
#include "Customer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::ostringstream;
using std::vector;

using namespace std;

string Customer::statement()
{
    ostringstream result;
    result << "Rental Record for " << getName() << "\n";
    result << getRentalList();
    // add footer lines
    result << "Amount owed is " << getTotalAmount() << "\n";
    result << "You earned " << getTotalPoint()
           << " frequent renter points";
    return result.str();
}

double Customer::getTotalAmount() {
    double totalAmount = 0;
    auto iter = _rentals.begin();
    auto iter_end = _rentals.end();
    for ( ; iter != iter_end; ++iter ) {
        double thisAmount = 0;
        auto each = *iter;

        // determine amounts for each line
        thisAmount += each->getRentalAmount();
        totalAmount += thisAmount;
    }
    return totalAmount;
}

int Customer::getTotalPoint() {
    int frequentRenterPoints = 0;
    auto iter = _rentals.begin();
    auto iter_end = _rentals.end();
    for ( ; iter != iter_end; ++iter ) {
        auto each = *iter;

        frequentRenterPoints += each->getMovie()->getPriceCode()->bonus(each->getDaysRented());
    }
    return frequentRenterPoints;
}

string Customer::getRentalList() {
    auto iter = _rentals.begin();
    auto iter_end = _rentals.end();
    ostringstream result;
    for ( ; iter != iter_end; ++iter ) {
        auto each = *iter;

        // show figures for this rental
        result << each->getInfo();
    }
    return result.str();
}