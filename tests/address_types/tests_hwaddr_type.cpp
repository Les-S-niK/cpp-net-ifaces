
#include <gtest/gtest.h>

#include "address_types/hwaddr.hpp"

TEST(TestHwAddrType, checkGetMethodReturnsValidData) {
    // NOLINTNEXTLINE
    HwAddr::hwaddr_t arr{0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5};
    HwAddr addr{arr};

    ASSERT_EQ(arr, addr.get());
}

TEST(TestHwAddrType, checkToStringReturnsCorrectRepresentation) {
    // NOLINTNEXTLINE
    HwAddr::hwaddr_t arr{0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5};
    HwAddr addr{arr};

    ASSERT_EQ("f0:f1:f2:f3:f4:f5", addr.toString());
}

TEST(TestHwAddrType, checkToStringReturnsCorrectRepresentationAllZeros) {
    HwAddr::hwaddr_t arr{0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    HwAddr addr{arr};

    ASSERT_EQ("00:00:00:00:00:00", addr.toString());
}
