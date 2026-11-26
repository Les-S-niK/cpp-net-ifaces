
#ifndef INCLUDE_SOCKETS_LINUX_SOCKETS_HPP_
#define INCLUDE_SOCKETS_LINUX_SOCKETS_HPP_

#include <expected>

#include "socket.hpp"

namespace sockets {

class LinuxSocket4 {
   public:
    LinuxSocket4(const LinuxSocket4&) = delete;
    LinuxSocket4(LinuxSocket4&& other) noexcept;
    auto operator=(const LinuxSocket4&) -> LinuxSocket4& = delete;
    auto operator=(LinuxSocket4&&) -> LinuxSocket4& = delete;
    ~LinuxSocket4() = default;

    [[nodiscard]] auto static create() noexcept
        -> std::expected<LinuxSocket4, SocketErrors>;
    [[nodiscard]] auto getFd() const noexcept -> fd_t;

   private:
    fd_t _fd;
};

class LinuxSocket6 {
   public:
    LinuxSocket6(const LinuxSocket6&) = delete;
    LinuxSocket6(LinuxSocket6&& other) noexcept;
    auto operator=(const LinuxSocket6&) -> LinuxSocket6& = delete;
    auto operator=(LinuxSocket6&& other) -> LinuxSocket6& = delete;
    ~LinuxSocket6();

    [[nodiscard]] auto static create() noexcept
        -> std::expected<LinuxSocket6, SocketErrors>;
    [[nodiscard]] auto getFd() const noexcept -> fd_t;

   private:
    fd_t _fd;
};

static_assert(Socket<LinuxSocket4>,
              "`LinuxSocket4` does not implement `Socket` concept.");
static_assert(Socket<LinuxSocket6>,
              "`LinuxSocket6` does not implement `Socket` concept.");
}  // namespace sockets

#endif  // INCLUDE_SOCKETS_LINUX_SOCKETS_HPP_
