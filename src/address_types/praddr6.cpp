
#include "address_types/praddr6.hpp"

#include <format>

PrAddr6::PrAddr6(praddr6_t praddr6) : _praddr6(praddr6) {}

[[nodiscard]] auto PrAddr6::get() const noexcept -> praddr6_t {
    return _praddr6;
}

[[nodiscard]] auto PrAddr6::toString() const noexcept -> std::string {
    std::string result{};
    constexpr auto result_string_size = 40;
    result.reserve(result_string_size);

    for (size_t index = 0; index < _praddr6.size(); index += 2) {
        result.append(std::format("{:02x}{:02x}", _praddr6.at(index),
                                  _praddr6.at(index + 1)));
        if (index < (size - 2)) {
            result.push_back(':');
        }
    }
    return result;
}
