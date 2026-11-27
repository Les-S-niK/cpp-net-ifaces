
#include <gtest/gtest.h>

#include "address_types/praddr4.hpp"

TEST(TestPrAddr4Type, checkGetMethodReturnsValidData) {
    // NOLINTNEXTLINE
    PrAddr4::praddr4_t arr{192, 168, 0, 100};
    PrAddr4 addr{arr};

    ASSERT_EQ(arr, addr.get());
}

TEST(TestPrAddr4Type, checkToStringReturnsCorrectRepresentation) {
    // NOLINTNEXTLINE
    PrAddr4::praddr4_t arr{192, 168, 0, 100};
    PrAddr4 addr{arr};

    ASSERT_EQ("192.168.0.100", addr.toString());
}

TEST(TestPrAddr4Type, checkToStringReturnsCorrectRepresentationAllZeros) {
    PrAddr4::praddr4_t arr{0, 0, 0, 0};
    PrAddr4 addr{arr};

    ASSERT_EQ("0.0.0.0", addr.toString());
}
