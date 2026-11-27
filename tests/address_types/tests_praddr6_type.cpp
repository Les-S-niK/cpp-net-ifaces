
#include <gtest/gtest.h>

#include "address_types/praddr6.hpp"

TEST(TestPrAddr6Type, checkGetMethodReturnsValidData) {
    PrAddr6::praddr6_t arr{
        // NOLINTNEXTLINE
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    };
    PrAddr6 addr{arr};

    ASSERT_EQ(arr, addr.get());
}

TEST(TestPrAddr6Type, checkToStringReturnsCorrectRepresentation) {
    PrAddr6::praddr6_t arr{
        // NOLINTNEXTLINE
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    };
    PrAddr6 addr{arr};

    ASSERT_EQ("2001:0db8:0000:0000:0000:0000:0000:0001", addr.toString());
}

TEST(TestPrAddr6Type, checkToStringReturnsCorrectRepresentationAllZeros) {
    PrAddr6::praddr6_t arr{};
    PrAddr6 addr{arr};

    ASSERT_EQ("0000:0000:0000:0000:0000:0000:0000:0000", addr.toString());
}
