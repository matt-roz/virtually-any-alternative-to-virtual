#ifndef VAATV_DEVICE_MANAGER_BASE_H
#define VAATV_DEVICE_MANAGER_BASE_H

#include <algorithm>
#include <functional>
#include <vector>

#include "concepts.h"

namespace vaatv::internal {

    template <concepts::device device_t>
    class device_manager_base {
    public:
        using device_type = device_t;
        using container_type = std::vector<device_type>;
        using ref_container_type = std::vector<std::reference_wrapper<device_type>>;

    protected:
        // region ops for all concept::device types
        void scan_devices() noexcept { m_devices = device_type::scan(); }
        void update_devices() noexcept { for (auto &device : m_devices) { device.update(); } }

        [[nodiscard]] ref_container_type devices() noexcept {
            ref_container_type result{};
            std::copy(m_devices.begin(), m_devices.end(), std::back_inserter(result));
            return result;
        }

        [[nodiscard]] ref_container_type filter_devices(const auto &predicate) noexcept {
            ref_container_type result{};
            std::copy_if(m_devices.begin(), m_devices.end(), std::back_inserter(result), predicate);
            return result;
        }
        // endregion

        // region ops for concept::user_device types
        void login_devices(const auto &error_callback) noexcept requires concepts::user_device<device_type> {
            for (auto &device : m_devices) {
                if (!device.login()) { error_callback(device); }
            }
        }

        void logout_devices() noexcept requires concepts::user_device<device_type> {
            for (auto &device : m_devices) { device.logout(); }
        }
        // endregion


    private:
        container_type m_devices{};
    };

}  // namespace vaatv::internal

#endif //VAATV_DEVICE_MANAGER_BASE_H
