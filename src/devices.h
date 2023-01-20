#ifndef VAATV_DEVICES_H
#define VAATV_DEVICES_H

#include <iostream>
#include <string>
#include <vector>

namespace vaatv {

    class switch_device {
    public:
        explicit switch_device(std::string identifier) : name(std::move(identifier)) {}

        [[nodiscard]] static std::vector<switch_device> scan() {
            return {switch_device("A"), switch_device("B"), switch_device("C")};
        }

        void update() const { std::cout << "Updating Switch " << name << std::endl; };
 
        std::string name{};
    };
    
    class dimmer_device {
    public:
        explicit dimmer_device(std::string identifier) : name(std::move(identifier)) {}

        [[nodiscard]] static std::vector<dimmer_device> scan() {
            return {dimmer_device("E"), dimmer_device("F"), dimmer_device("G")};
        }

        void update() const { std::cout << "Updating Dimmer " << name << std::endl; };

        std::string name{};
    };

    class thermo_device {
    public:
        explicit thermo_device(std::string identifier) : name(std::move(identifier)) {}

        [[nodiscard]] static std::vector<thermo_device> scan() {
            return {thermo_device("H"), thermo_device("I")};
        }

        void update() const { std::cout << "Updating Thermo " << name << (m_logged_in ? "" : " failed: authorization required ") << std::endl; };
        bool login() { std::cout << "Login Thermo " << name << std::endl; return m_logged_in = true; };
        void logout() { std::cout << "Logout Thermo " << name << std::endl; m_logged_in = false; };

        std::string name{};

    private:
        bool m_logged_in{false};
    };

    class outlet_device {
    public:
        explicit outlet_device(std::string identifier) : name(std::move(identifier)) {}

        [[nodiscard]] static std::vector<outlet_device> scan() {
            return {outlet_device("K"), outlet_device("L"), outlet_device("M")};
        }

        void update() const { std::cout << "Updating Outlet " << name << (m_logged_in ? "" : " failed: authorization required ") << std::endl; };
        bool login() { std::cout << "Login Outlet " << name << std::endl; return m_logged_in = true; };
        void logout() { std::cout << "Logout Outlet " << name << std::endl; m_logged_in = false; };

        std::string name{};

    private:
        bool m_logged_in{false};
    };

    class imposter_device {
    public:
        [[nodiscard]] static std::vector<imposter_device> scan() { return {}; }
        void update() const { }
    };


}  // namespace vaatv

#endif //VAATV_DEVICES_H
