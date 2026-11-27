#include "address_types/hwaddr.hpp"

#include <cstddef>
#include <format>
#include <ranges>

HwAddr::HwAddr(hwaddr_t hwaddr) noexcept : _hwaddr(hwaddr) {}

[[nodiscard]] auto HwAddr::get() const noexcept -> hwaddr_t { return _hwaddr; }

[[nodiscard]] auto HwAddr::toString() const noexcept -> std::string {
    std::string result{};
    constexpr auto result_string_size = static_cast<size_t>(size * 3);
    result.reserve(result_string_size);

    using std::ranges::views::enumerate;
    for (auto [index, byte] : enumerate(_hwaddr)) {
        result.append(std::format("{:02x}", byte));
        if (index < (size - 1)) {
            result.push_back(':');
        }
    }
    return result;
}
