
#include "system/sockets/linux_sockets.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <expected>
#include <utility>

#include "system/sockets/socket.hpp"

namespace {
using sockets::fd_t;

auto closeSocket(fd_t sock_fd) noexcept -> void {
    shutdown(sock_fd, SHUT_RDWR);
    close(sock_fd);
}
}  // namespace

namespace sockets {

LinuxSocket4::LinuxSocket4(LinuxSocket4&& other) noexcept {
    _fd = std::exchange(other._fd, -1);
}
LinuxSocket4::~LinuxSocket4() { closeSocket(_fd); }
[[nodiscard]] auto LinuxSocket4::create() noexcept
    -> std::expected<LinuxSocket4, SocketErrors> {
    fd_t sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1) {
        return std::unexpected{SocketErrors::CanNotCreate};
    }
    return LinuxSocket4{sock_fd};
}
[[nodiscard]] auto LinuxSocket4::getFd() const noexcept -> fd_t { return _fd; }
LinuxSocket4::LinuxSocket4(fd_t sock4_fd) noexcept : _fd(sock4_fd) {}

LinuxSocket6::LinuxSocket6(LinuxSocket6&& other) noexcept {
    _fd = std::exchange(other._fd, -1);
}
LinuxSocket6::~LinuxSocket6() { closeSocket(_fd); }
[[nodiscard]] auto LinuxSocket6::create() noexcept
    -> std::expected<LinuxSocket6, SocketErrors> {
    fd_t sock_fd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (sock_fd == -1) {
        return std::unexpected{SocketErrors::CanNotCreate};
    }
    return LinuxSocket6{sock_fd};
}
[[nodiscard]] auto LinuxSocket6::getFd() const noexcept -> fd_t { return _fd; }
LinuxSocket6::LinuxSocket6(fd_t sock6_fd) noexcept : _fd(sock6_fd) {}

}  // namespace sockets
