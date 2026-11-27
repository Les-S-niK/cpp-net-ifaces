
#ifndef INCLUDE_SOCKETS_SOCKET_HPP_
#define INCLUDE_SOCKETS_SOCKET_HPP_

#include <concepts>
#include <expected>

#include "number_usings.hpp"

namespace sockets {
using fd_t = i32;

enum class SocketErrors : u8 { CanNotCreate };

template <typename Sock>
concept Socket = requires(Sock sock) {
    { sock.create() } -> std::same_as<std::expected<Sock, SocketErrors>>;
    { sock.getFd() } -> std::same_as<fd_t>;
};

}  // namespace sockets
#endif  // INCLUDE_SOCKETS_SOCKET_HPP_
