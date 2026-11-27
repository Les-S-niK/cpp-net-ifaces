
#ifndef INCLUDE_IFREQ_IFREQ_HPP_
#define INCLUDE_IFREQ_IFREQ_HPP_

#include <net/if.h>

#include <concepts>
#include <expected>
#include <string>
#include <string_view>

#include "address_types/hwaddr.hpp"
#include "address_types/praddr4.hpp"
#include "address_types/praddr6.hpp"

namespace ifrequests {

using flags_t = u32;

enum class IfaceReqErrors : u8 { CanNotCreate };

template <typename IfaceReq>
concept SysNetIfaceReq = requires(IfaceReq req, std::string&& iface_name) {
    {
        req.create(std::move(iface_name))
    } -> std::same_as<std::expected<IfaceReq, IfaceReqErrors>>;
    { req.getName() } -> std::same_as<std::string>;
    { req.getNameView() } -> std::same_as<std::string_view>;
    { req.getHwAddr() } -> std::same_as<HwAddr>;
    { req.getPrAddr4() } -> std::same_as<PrAddr4>;
    { req.getPrAddr6() } -> std::same_as<PrAddr6>;
    { req.getMTU() } -> std::same_as<u32>;
    { req.getFlags() } -> std::same_as<flags_t>;
};
}  // namespace ifrequests

#endif  // INCLUDE_IFREQ_IFREQ_HPP_
