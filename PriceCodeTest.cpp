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

TEST(ChildrensTestAmount, getAmount){
    Childrens childrens;

    EXPECT_EQ(childrens.getAmount(0), 0);
    EXPECT_EQ(childrens.getAmount(10), 30);
    EXPECT_GT(childrens.getAmount(-1), -1);
}

TEST(NewReleaseTestAmount, getAmount){
    NewRelease newRelease;

    EXPECT_EQ(newRelease.getAmount(0), 0);
    EXPECT_EQ(newRelease.getAmount(10), 12);
    EXPECT_GT(newRelease.getAmount(-1), -1);
}

TEST(RegularTestBonus, getAmount){
    Regular regular;

    EXPECT_EQ(regular.bonus(0), 1);
    EXPECT_EQ(regular.bonus(10), 1);
    EXPECT_EQ(regular.bonus(-1), 1);
}

TEST(ChildrensTestBonus, getAmount){
    Childrens childrens;

    EXPECT_EQ(childrens.bonus(0), 1);
    EXPECT_EQ(childrens.bonus(10), 1);
    EXPECT_EQ(childrens.bonus(-1), 1);
}