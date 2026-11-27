
#ifndef INCLUDE_ADDRESS_TYPES_PRADDR4_HPP_
#define INCLUDE_ADDRESS_TYPES_PRADDR4_HPP_

#include <array>
#include <format>
#include <ranges>
#include <string>

#include "number_usings.hpp"

class PrAddr4 {
   public:
    static constexpr u8 size = 4;
    using praddr4_t = std::array<u8, size>;

    explicit PrAddr4(praddr4_t praddr4) noexcept;
    [[nodiscard]] auto get() const noexcept -> praddr4_t;
    [[nodiscard]] auto toString() const noexcept -> std::string {
        std::string result{};
        constexpr auto result_string_size = static_cast<size_t>(size * 4);
        result.reserve(result_string_size);

        using std::ranges::views::enumerate;
        for (auto [index, byte] : enumerate(_praddr4)) {
            result.append(std::format("{}", byte));
            if (index < (size - 1)) {
                result.push_back('.');
            }
        }
        return result;
    }

   private:
    praddr4_t _praddr4;
};

#endif  // INCLUDE_ADDRESS_TYPES_PRADDR4_HPP_
