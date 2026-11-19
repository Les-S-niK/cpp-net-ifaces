#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <string>

#include "address_types/hwaddr.hpp"
#include "address_types/praddr4.hpp"
#include "address_types/praddr6.hpp"

namespace {

// Build a PrAddr6::praddr6_t from 8 uint16 groups (more readable than 16 u8s).
auto make6(const std::array<std::uint16_t, 8>& groups) -> PrAddr6::praddr6_t {
    PrAddr6::praddr6_t out{};
    for (std::size_t i = 0; i < groups.size(); ++i) {
        out.at(2 * i) = static_cast<std::uint8_t>((groups[i] >> 8) & 0xFFu);
        out.at(2 * i + 1) = static_cast<std::uint8_t>(groups[i] & 0xFFu);
    }
    return out;
}

TEST(PrAddr4Get, RoundTripsRepresentativeValues) {
    const std::array<PrAddr4::praddr4_t, 6> cases{
        {
            {0, 0, 0, 0},
            {127, 0, 0, 1},
            {192, 168, 0, 1},
            {10, 20, 30, 40},
            {1, 2, 3, 4},
            {255, 255, 255, 255},
        },
    };
    for (const auto& c : cases) {
        const PrAddr4 a{c};
        EXPECT_EQ(a.get(), c);
    }
}

TEST(PrAddr4Get, ReturnsIndependentCopy) {
    PrAddr4 a{PrAddr4::praddr4_t{1, 2, 3, 4}};
    auto copy = a.get();
    copy.at(0) = 99;
    EXPECT_EQ(a.get().at(0), 1);
}

TEST(PrAddr4Get, IsConstCallable) {
    const PrAddr4 a{PrAddr4::praddr4_t{1, 2, 3, 4}};
    EXPECT_EQ(a.get(), (PrAddr4::praddr4_t{1, 2, 3, 4}));
}

TEST(PrAddr6Get, RoundTripsRepresentativeValues) {
    const std::array<PrAddr6::praddr6_t, 4> cases{{
        make6({0, 0, 0, 0, 0, 0, 0, 0}),
        make6({0, 0, 0, 0, 0, 0, 0, 1}),
        make6({0x2001, 0x0db8, 0, 0, 0, 0, 0, 1}),
        make6({0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff}),
    }};
    for (const auto& c : cases) {
        const PrAddr6 a{c};
        EXPECT_EQ(a.get(), c);
    }
}

TEST(PrAddr6Get, ReturnsIndependentCopy) {
    PrAddr6 a{make6({1, 2, 3, 4, 5, 6, 7, 8})};
    auto copy = a.get();
    copy[0] = 0xFF;
    EXPECT_EQ(a.get()[0], 0x00);
}

TEST(PrAddr6Get, IsConstCallable) {
    const PrAddr6 a{make6({1, 2, 3, 4, 5, 6, 7, 8})};
    EXPECT_EQ(a.get(), make6({1, 2, 3, 4, 5, 6, 7, 8}));
}

TEST(HwAddrGet, RoundTripsRepresentativeValues) {
    const std::array<HwAddr::hwaddr_t, 5> cases{
        {
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
            {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
            {0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
            {0xde, 0xad, 0xbe, 0xef, 0x00, 0x01},
        },
    };
    for (const auto& c : cases) {
        const HwAddr a{c};
        EXPECT_EQ(a.get(), c);
    }
}

TEST(HwAddrGet, ReturnsIndependentCopy) {
    HwAddr a{HwAddr::hwaddr_t{1, 2, 3, 4, 5, 6}};
    auto copy = a.get();
    copy.at(0) = 0xAA;
    EXPECT_EQ(a.get().at(0), 0x01);
}

TEST(HwAddrGet, IsConstCallable) {
    const HwAddr a{HwAddr::hwaddr_t{0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}};
    EXPECT_EQ(a.get(), (HwAddr::hwaddr_t{0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}));
}

struct PrAddr4ToStringParam {
    PrAddr4::praddr4_t addr;
    std::string expected;
};

class PrAddr4ToString : public ::testing::TestWithParam<PrAddr4ToStringParam> {
};

TEST_P(PrAddr4ToString, ProducesDottedDecimal) {
    const PrAddr4 a{GetParam().addr};
    EXPECT_EQ(a.toString(), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    StandardForms, PrAddr4ToString,
    ::testing::Values(PrAddr4ToStringParam{{0, 0, 0, 0}, "0.0.0.0"},
                      PrAddr4ToStringParam{{0, 0, 0, 1}, "0.0.0.1"},
                      PrAddr4ToStringParam{{127, 0, 0, 1}, "127.0.0.1"},
                      PrAddr4ToStringParam{{192, 168, 1, 10}, "192.168.1.10"},
                      PrAddr4ToStringParam{{1, 2, 3, 4}, "1.2.3.4"},
                      PrAddr4ToStringParam{{255, 255, 255, 255},
                                           "255.255.255.255"}));

struct PrAddr6ToStringParam {
    std::array<std::uint16_t, 8> groups;
    std::string expected;
};

class PrAddr6ToString : public testing::TestWithParam<PrAddr6ToStringParam> {};

TEST_P(PrAddr6ToString, ProducesFullUncompressedLowercaseForm) {
    const PrAddr6 a{make6(GetParam().groups)};
    EXPECT_EQ(a.toString(), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    StandardForms, PrAddr6ToString,
    ::testing::Values(
        // :: (all zeros)
        PrAddr6ToStringParam{{0, 0, 0, 0, 0, 0, 0, 0},
                             "0000:0000:0000:0000:0000:0000:0000:0000"},
        // ::1  -- the example from the task description
        PrAddr6ToStringParam{{0, 0, 0, 0, 0, 0, 0, 1},
                             "0000:0000:0000:0000:0000:0000:0000:0001"},
        // all ones
        PrAddr6ToStringParam{
            {0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff},
            "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"},
        // 2001:db8::1 written out fully (leading zeros must be kept)
        PrAddr6ToStringParam{{0x2001, 0x0db8, 0, 0, 0, 0, 0, 1},
                             "2001:0db8:0000:0000:0000:0000:0000:0001"},
        // arbitrary, all 4 hex digits present
        PrAddr6ToStringParam{
            {0xabcd, 0x1234, 0x5678, 0x9abc, 0xdef0, 0x1111, 0x2222, 0x3333},
            "abcd:1234:5678:9abc:def0:1111:2222:3333"}));

struct HwAddrToStringParam {
    HwAddr::hwaddr_t addr;
    std::string expected;
};

class HwAddrToString : public ::testing::TestWithParam<HwAddrToStringParam> {};

TEST_P(HwAddrToString, ProducesColonSeparatedLowercaseHex) {
    const HwAddr a{GetParam().addr};
    EXPECT_EQ(a.toString(), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    StandardForms, HwAddrToString,
    ::testing::Values(HwAddrToStringParam{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
                                          "00:00:00:00:00:00"},
                      // the example from the task description (with single ':')
                      HwAddrToStringParam{{0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
                                          "ff:ff:ff:ff:ff:ff"},
                      HwAddrToStringParam{{0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
                                          "aa:bb:cc:dd:ee:ff"},
                      // must keep the leading zero in each byte
                      HwAddrToStringParam{{0x01, 0x02, 0x03, 0x04, 0x05, 0x06},
                                          "01:02:03:04:05:06"},
                      HwAddrToStringParam{{0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f},
                                          "0a:0b:0c:0d:0e:0f"}));
}  // namespace
