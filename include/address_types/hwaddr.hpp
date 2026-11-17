
#ifndef INCLUDE_ADDRESS_TYPES_HWADDR_HPP_
#define INCLUDE_ADDRESS_TYPES_HWADDR_HPP_

#include <array>
#include <string>

#include "number_usings.hpp"
class HwAddr {
   public:
    static constexpr u8 size = 6;
    using hwaddr_t = std::array<u8, size>;

    constexpr explicit HwAddr(hwaddr_t hwaddr);
    [[nodiscard]] constexpr auto get() const noexcept -> hwaddr_t;
    [[nodiscard]] auto toString() const noexcept -> std::string;

   private:
    hwaddr_t _hwaddr;
};

#endif  // INCLUDE_ADDRESS_TYPES_HWADDR_HPP_
