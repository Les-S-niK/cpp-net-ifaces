
#ifndef INCLUDE_ADDRESS_TYPES_PRADDR4_HPP_
#define INCLUDE_ADDRESS_TYPES_PRADDR4_HPP_

#include <array>
#include <string>

#include "number_usings.hpp"

class PrAddr4 {
   public:
    static constexpr u8 size = 4;
    using praddr4_t = std::array<u8, size>;

    explicit PrAddr4(praddr4_t praddr4) noexcept;
    [[nodiscard]] auto get() const noexcept -> praddr4_t;
    [[nodiscard]] auto toString() const noexcept -> std::string;

   private:
    praddr4_t _praddr4;
};

#endif  // INCLUDE_ADDRESS_TYPES_PRADDR4_HPP_
