
#include <gtest/gtest.h>

#include "system/sockets/linux_sockets.hpp"
#include "system/sockets/socket.hpp"

namespace {

template <sockets::Socket T>
auto checkLinuxSocketCreate() -> bool {
    auto sock = T::create();
    return sock.has_value();
}

template <sockets::Socket T>
auto checkLinuxSocketReturnsValidFd() -> bool {
    auto sock = T::create();
    return sock.value().getFd() != -1;
}

}  // namespace

TEST(SystemLinuxSockets4, canCreateNewInstanceWithoutErrors) {
    ASSERT_TRUE(checkLinuxSocketCreate<sockets::LinuxSocket4>());
}

TEST(SystemLinuxSockets4, getFdReturnsValidSocketFd) {
    ASSERT_TRUE(checkLinuxSocketReturnsValidFd<sockets::LinuxSocket4>());
}

TEST(SystemLinuxSockets6, canCreateNewInstanceWithoutErrors) {
    ASSERT_TRUE(checkLinuxSocketCreate<sockets::LinuxSocket6>());
}

TEST(SystemLinuxSockets6, getFdReturnsValidSocketFd) {
    ASSERT_TRUE(checkLinuxSocketReturnsValidFd<sockets::LinuxSocket6>());
}
