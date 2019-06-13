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
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    auto iter = _rentals.begin();
    auto iter_end = _rentals.end();
    ostringstream result;
    result << "Rental Record for " << getName() << "\n";
    for ( ; iter != iter_end; ++iter ) {
        double thisAmount = 0;
        auto each = *iter;

        // determine amounts for each line
        thisAmount += each->getMovie()->getPriceCode()->getAmount(each->getDaysRented());

        // add frequent renter points
        frequentRenterPoints++;
        // add bonus for a two day new release rental
        if ( ( each->getMovie()->getPriceCode()->bonus())
             && each->getDaysRented() > 1 ) frequentRenterPoints++;

        // show figures for this rental
        result << "\t" << each->getMovie()->getTitle() << "\t"
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
    explicit MockCustomer(const string& name);
};

MockCustomer::MockCustomer(const string& name) : Customer(name) {}

class MockRegular : public Regular {
public:
    MOCK_CONST_METHOD0(bonus, bool());
    MOCK_CONST_METHOD1(getAmount, double(const int days));
};

class MockChildrens : public Childrens {
public:
    MOCK_CONST_METHOD0(bonus, bool());
    MOCK_CONST_METHOD1(getAmount, double(const int days));
};

class MockNewRelease : public NewRelease {
public:
    MOCK_CONST_METHOD0(bonus, bool());
    MOCK_CONST_METHOD1(getAmount, double(const int days));
};

class MockMovie : public Movie {
public:
    MockMovie(const string& title, const std::shared_ptr<PriceCode> &price);
    MOCK_CONST_METHOD0(getPriceCode, std::shared_ptr<PriceCode>());
    MOCK_CONST_METHOD0(getTitle, string());
};

MockMovie::MockMovie(const string &title, const std::shared_ptr<PriceCode> &price) : Movie(title, price) {}

class MockRental : public Rental {
public:
    MockRental(const std::shared_ptr<Movie> &movie, const int& daysRented);
    MOCK_CONST_METHOD0(getDaysRented, int());
    MOCK_CONST_METHOD0(getMovie, std::shared_ptr<Movie>());
};

MockRental::MockRental(const std::shared_ptr<Movie> &movie, const int& daysRented) : Rental(movie, daysRented) {}

class MockPriceCode : public PriceCode {
public:
    MOCK_CONST_METHOD0(bonus, bool());
    MOCK_CONST_METHOD1(getAmount, double(const int& days));
};


using ::testing::Return;
using ::testing::_;
using ::testing::ReturnRef;
using ::testing::Return;

//Mock test
TEST(CustomerTest, Statement){
    MockCustomer customer("test");
    shared_ptr<MockChildrens> priceCode = shared_ptr<MockChildrens>(new MockChildrens());
    shared_ptr<MockMovie> movie = shared_ptr<MockMovie>(new MockMovie("licorne", priceCode));
    shared_ptr<MockRental> rental = shared_ptr<MockRental>(new MockRental(movie, 10));

    EXPECT_CALL(*movie, getPriceCode()).WillRepeatedly(Return(priceCode));
    EXPECT_CALL(*movie, getTitle()).WillRepeatedly(Return("licorne le retour"));

    EXPECT_CALL(*rental, getDaysRented()).WillRepeatedly(Return(666));
    EXPECT_CALL(*rental, getMovie()).WillRepeatedly(Return(movie));

    EXPECT_CALL(*priceCode, getAmount(rental->getDaysRented())).WillRepeatedly(Return(200));
    EXPECT_CALL(*priceCode, bonus()).WillRepeatedly(Return(false));

    EXPECT_EQ(customer.statement(), "Rental Record for test\nAmount owed is 0\nYou earned 0 frequent renter points");
    customer.addRental(rental);
    EXPECT_EQ(rental->getMovie()->getPriceCode()->getAmount(rental->getDaysRented()), 200);
}
