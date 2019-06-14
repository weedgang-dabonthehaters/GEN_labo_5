#include <memory>

#include <iostream>

//#include "Customer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "CustomerTest.cpp"
#include "PriceCodeTest.cpp"

int main() {

//    Customer customer("Olivier");
//    customer.addRental( std::make_shared<Rental>(Rental(std::make_shared<Movie>(Movie("Karate Kid")), 7)));
//    customer.addRental( std::make_shared<Rental>(Rental(std::make_shared<Movie>(Movie( "Avengers: Endgame", std::make_shared<NewRelease>(NewRelease()))), 5)));
//    customer.addRental( std::make_shared<Rental>(Rental(std::make_shared<Movie>(Movie("Snow White", std::make_shared<Childrens>(Childrens()))), 3 )));
//
//    std::cout << customer.statement() << std::endl;
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}