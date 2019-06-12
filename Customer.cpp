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
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    vector< Rental >::iterator iter = _rentals.begin();
    vector< Rental >::iterator iter_end = _rentals.end();
    ostringstream result;
    result << "Rental Record for " << getName() << "\n";
    for ( ; iter != iter_end; ++iter ) {
        double thisAmount = 0;
        Rental each = *iter;

        // determine amounts for each line
        switch ( each.getMovie()->getPriceCode() ) {
            case Movie::REGULAR:
                thisAmount += 2;
                if ( each.getDaysRented() > 2 )
                    thisAmount += ( each.getDaysRented() - 2 ) * 1.5 ;
                break;
            case Movie::NEW_RELEASE:
                thisAmount += each.getDaysRented() * 3;
                break;
            case Movie::CHILDRENS:
                thisAmount += 1.5;
                if ( each.getDaysRented() > 3 )
                    thisAmount += ( each.getDaysRented() - 3 ) * 1.5;
                break;
        }

        // add frequent renter points
        frequentRenterPoints++;
        // add bonus for a two day new release rental
        if ( ( each.getMovie()->getPriceCode() == Movie::NEW_RELEASE )
             && each.getDaysRented() > 1 ) frequentRenterPoints++;

        // show figures for this rental
        result << "\t" << each.getMovie()->getTitle() << "\t"
               << thisAmount << "\n";
        totalAmount += thisAmount;
    }
    // add footer lines
    result << "Amount owed is " << totalAmount << "\n";
    result << "You earned " << frequentRenterPoints
           << " frequent renter points";
    return result.str();
}

// Mock class
class MockCustomer : public Customer {
public:
    MockCustomer(string name) : Customer(name) {}
};

class MockMovie : public Movie {
public:
    MockMovie(string title, int price) : Movie(title, price) {}
    MOCK_CONST_METHOD0(getPriceCode, int());
    MOCK_CONST_METHOD0(getTitle, string());
};

class MockRental : public Rental {
public:
    MockRental(const Movie* movie, int daysRented) : Rental(movie, daysRented) {}
    MOCK_CONST_METHOD0(getDaysRented, int());
    MOCK_CONST_METHOD0(getMovie, Movie*());
};

using ::testing::Return;
using ::testing::_;
using ::testing::ReturnRef;
using ::testing::Return;

//Mock test
TEST(CustomerTest, Statement){
    MockCustomer customer("test");
    MockMovie* movie = new MockMovie("licorne", 10);
    MockRental rental(movie, 10);

    EXPECT_CALL(*movie, getPriceCode()).WillRepeatedly(Return(MockMovie::NEW_RELEASE));
    EXPECT_CALL(*movie, getTitle()).WillRepeatedly(Return("licorne le retour"));

    EXPECT_CALL(rental, getDaysRented()).WillRepeatedly(Return(666));
    EXPECT_CALL(rental, getMovie()).WillRepeatedly(Return(movie));
Movie* m = movie;
    EXPECT_EQ(m->getTitle(), "");

    //EXPECT_EQ(customer.statement(), "Rental Record for test\nAmount owed is 0\nYou earned 0 frequent renter points");
    //customer.addRental(rental);
    //EXPECT_EQ(customer.statement(), "Rental Record for test\n\tlicorne\t30\nAmount owed is 30\nYou earned 2 frequent renter points");
}
