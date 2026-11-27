#ifndef INCLUDE_ADDRESS_TYPES_PRADDR6_HPP_
#define INCLUDE_ADDRESS_TYPES_PRADDR6_HPP_

#include <array>
#include <string>

#include "number_usings.hpp"
class PrAddr6 {
   public:
    static constexpr u8 size = 16;
    using praddr6_t = std::array<u8, size>;

    explicit PrAddr6(praddr6_t praddr6);
    [[nodiscard]] auto get() const noexcept -> praddr6_t;
    [[nodiscard]] auto toString() const noexcept -> std::string;

   private:
    praddr6_t _praddr6;
};

#endif  // INCLUDE_ADDRESS_TYPES_PRADDR6_HPP_
