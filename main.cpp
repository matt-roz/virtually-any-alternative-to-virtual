#include <iostream>

#include "src/devices.h"
#include "src/device_manager.h"

using namespace vaatv; // NOLINT(google-build-using-namespace)

int main() {
    device_manager<switch_device, thermo_device, dimmer_device, outlet_device> dm{};
    dm.scan(); // scan for all device in declaration order

    dm.login<outlet_device>(); // login to all outlet_devices

    dm.update<dimmer_device, switch_device>(); // update all devices in type-order (dimmers first, then switches)
    dm.update(); // update all devices in declaration order (fails for all thermo_devices since they require authorization login)

    dm.login<thermo_device>();  // login to all thermo_devices
    dm.update<thermo_device>(); // update all thermo_devices

    // filter by predicate
    constexpr auto pred = []([[maybe_unused]] concepts::device auto &device) -> bool { return device.name == "E"; };
    auto [switches, dimmers] = dm.filter<switch_device, dimmer_device>(pred);

    std::cout << "Filtered Switches: " << std::endl;
    for (auto &device : switches) {
        device.get().update();  // there is no switch named E
    }

    std::cout << "Filtered Dimmers: " << std::endl;
    for (auto &device : dimmers) {
        device.get().name = device.get().name + " Mutated"; // there is exactly 1 dimmer named "E"
    }

    // check if mutation was persistent
    auto [check_dimmers] = dm.get<dimmer_device>();
    std::cout << "Mutated Dimmers: " << std::endl;
    for (auto &device : check_dimmers) {
        device.get().update();
    }

    dm.logout(); // logout all authorization devices in declaration order (first thermos, then outlets)
}
