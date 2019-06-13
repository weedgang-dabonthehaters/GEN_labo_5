//
// Created by gaetan on 13.06.19.
//

#include "PriceCode.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::Return;
using ::testing::_;
using ::testing::ReturnRef;
using ::testing::Return;

//Mock test
TEST(RegularTestAmount, getAmount){
    Regular regular;

    EXPECT_EQ(regular.getAmount(0), 0);
    EXPECT_EQ(regular.getAmount(10), 14);
    EXPECT_GT(regular.getAmount(-1), -1);
}