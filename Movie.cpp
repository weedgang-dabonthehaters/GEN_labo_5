#include "Movie.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

using ::testing::Return;
using ::testing::_;
using ::testing::ReturnRef;
using ::testing::Return;

const int Movie::CHILDRENS;
const int Movie::REGULAR;
const int Movie::NEW_RELEASE;

//Mock test
TEST(MovieTest, getPriceCode){
    Movie m("GEN");
    EXPECT_EQ(m.getTitle(), "GEN");
    EXPECT_EQ(m.getPriceCode(), Movie::REGULAR);
    m.setPriceCode(Movie::NEW_RELEASE);
    EXPECT_EQ(m.getPriceCode(), Movie::NEW_RELEASE);
}