
#ifndef INCLUDE_IFREQ_LINUX_IFREQ_HPP_
#define INCLUDE_IFREQ_LINUX_IFREQ_HPP_

#include <net/if.h>

#include "address_types/hwaddr.hpp"
#include "address_types/praddr4.hpp"
#include "address_types/praddr6.hpp"
#include "system/ifreq/ifreq.hpp"
#include "system/sockets/linux_sockets.hpp"

namespace ifrequests {

class LinuxSysNetIfaceReq {
    using LinuxSocket4 = sockets::LinuxSocket4;
    using LinuxSocket6 = sockets::LinuxSocket6;

   public:
    auto static create(std::string&& name) noexcept
        -> std::expected<LinuxSysNetIfaceReq, IfaceReqErrors>;
    [[nodiscard]] auto getName() const noexcept -> std::string;
    [[nodiscard]] auto getNameView() const noexcept -> std::string_view;
    [[nodiscard]] auto getHwAddr() const noexcept -> HwAddr;
    [[nodiscard]] auto getPrAddr4() const noexcept -> PrAddr4;
    [[nodiscard]] auto getPrAddr6() const noexcept -> PrAddr6;
    [[nodiscard]] auto getMTU() const noexcept -> u32;
    [[nodiscard]] auto getFlags() const noexcept -> flags_t;

   private:
    std::string _name;
    HwAddr _hwaddr;
    PrAddr4 _praddr4;
    PrAddr6 _praddr6;
    u32 _mtu;
    flags_t _flags;
    LinuxSocket4 _sock4;
    LinuxSocket6 _sock6;

    explicit LinuxSysNetIfaceReq(std::string&& name) noexcept;
    auto fillMainFields() noexcept -> void;
    auto fillHwAddr() noexcept -> void;
    auto fillPrAddr4() noexcept -> void;
    auto fillPrAddr6() noexcept -> void;
    auto fillMTU() noexcept -> void;
    auto fillFlags() noexcept -> void;
    auto getIfreq() noexcept -> struct ifreq;
};

static_assert(
    SysNetIfaceReq<LinuxSysNetIfaceReq>,
    "`LinuxSysNetIfaceReq` does not satisfy `SysNetIfaceReq` concept.");
}  // namespace ifrequests

#endif  // INCLUDE_IFREQ_LINUX_IFREQ_HPP_
