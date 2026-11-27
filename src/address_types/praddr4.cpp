
#include "address_types/praddr4.hpp"

#include <format>
#include <ranges>

PrAddr4::PrAddr4(praddr4_t praddr4) noexcept : _praddr4{praddr4} {}

[[nodiscard]] auto PrAddr4::get() const noexcept -> praddr4_t {
    return _praddr4;
}
[[nodiscard]] auto PrAddr4::toString() const noexcept -> std::string {
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
