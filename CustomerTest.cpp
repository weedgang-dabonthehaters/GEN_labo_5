//
// Created by gaetan on 14.06.19.
//

#include <memory>

//#include "Customer.h"
// Nous avons cherche avec l'assistant comment faire le lien entre le .h et le .cpp de
// customer mais nous n'avons pas reussi a trouver la nature du problème.
// Nous avons donc inclut le fichier cpp
#include "Customer.cpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

// Mock class
class MockCustomer : public Customer {
public:
    explicit MockCustomer(const string& name);
    MOCK_METHOD0(getTotalAmount, double());
    MOCK_METHOD0(getTotalPoint, int());
    MOCK_METHOD0(getRentalList, string());
};

MockCustomer::MockCustomer(const string& name) : Customer(name) {}


using ::testing::Return;
using ::testing::_;
using ::testing::ReturnRef;
using ::testing::Return;

//Mock test
TEST(CustomerTestMock, Statement){
std::shared_ptr<MockCustomer> customer = std::shared_ptr<MockCustomer>(new MockCustomer("test"));

EXPECT_CALL(*customer, getTotalAmount()).WillRepeatedly(Return(200));
EXPECT_CALL(*customer, getTotalPoint()).WillRepeatedly(Return(2));
EXPECT_CALL(*customer, getRentalList()).WillRepeatedly(Return("\tlicorne le retour\t100\n\tla generation GEN\t100\n"));


EXPECT_EQ(customer->statement(), "Rental Record for test\n\tlicorne le retour\t100\n\tla generation GEN\t100\nAmount owed is 200\nYou earned 2 frequent renter points");
}

//Mock test
TEST(CustomerTestEmpty, Statement){
std::shared_ptr<MockCustomer> customer = std::shared_ptr<MockCustomer>(new MockCustomer("test"));

EXPECT_CALL(*customer, getTotalAmount());
EXPECT_CALL(*customer, getTotalPoint());
EXPECT_CALL(*customer, getRentalList());

EXPECT_EQ(customer->statement(), "Rental Record for test\nAmount owed is 0\nYou earned 0 frequent renter points");
}
