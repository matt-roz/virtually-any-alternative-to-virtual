#ifndef VAATV_DEVICE_MANAGER_H
#define VAATV_DEVICE_MANAGER_H

#include <iostream>

#include <tuple>

#include "concepts.h"
#include "type_traits.h"
#include "device_manager_base.h"

namespace vaatv {

    namespace internal {
        constexpr static auto default_error_callback = []([[maybe_unused]] const auto &device){ return; };
    }

    template <concepts::device ... Ds>
    class device_manager final : public internal::device_manager_base<Ds> ... {
    public:
        using device_types = std::tuple<Ds ... >;
        using user_device_types = traits::tuple_filter_t<device_types, traits::is_user_device>;

    // region concepts::device ops (all devices)
        /* update all 'concepts::device ... Ts' in order of call-site */
        template <concepts::device ... Ts> requires (traits::any_same_v<Ts, Ds ... > and ... )
        void update() { (internal::device_manager_base<Ts>::update_devices(), ... ); }
        
        /* update all 'concepts::device ... Ds' in order of device_manager type declaration */
        void update() { update<Ds ... >(); }

        /* scan all 'concepts::device ... Ts' in order of call-site */
        template <concepts::device ... Ts> requires (traits::any_same_v<Ts, Ds ... > and ... )
        void scan() { (internal::device_manager_base<Ts>::scan_devices(), ... ); }
        
        /* scan all 'concepts::device ... Ds' in order of device_manager type declaration */
        void scan() { scan<Ds ... >(); }

        /* get all 'concepts::device ... Ts' in order of call-site */
        template <concepts::device ... Ts> requires (traits::any_same_v<Ts, Ds ... > and ... )
        [[nodiscard]] decltype(auto) get() { return std::make_tuple(internal::device_manager_base<Ts>::devices() ... ); }
        
        /* get all 'concepts::device ... Ds' in order of device_manager type declaration */
        [[nodiscard]] decltype(auto) get() { return get<Ds ... >(); }

        /* filer by user-defined predicate all 'concepts::device ... Ts' in order of call-site */
        template <concepts::device ... Ts> requires (traits::any_same_v<Ts, Ds ... > and ... )
        [[nodiscard]] decltype(auto) filter(const auto &predicate) { return std::make_tuple(internal::device_manager_base<Ts>::filter_devices(predicate) ... ); }
        
        /* filer by user-defined predicate all 'concepts::device ... Ds' in order of device_manager type declaration */
        [[nodiscard]] decltype(auto) filter(const auto &predicate) { return filter<Ds ... >(predicate); }
    // endregion

    // region concepts::user_device ops (user_device requires authorization)
        /* login to all 'concepts::user_device ... Ts' in order of call-site */
        template <concepts::user_device ... Ts> requires (traits::any_same_v<Ts, Ds ... > and ... )
        void login() { (internal::device_manager_base<Ts>::login_devices(internal::default_error_callback), ...); }

        /* login to all 'concepts::device ... Ds' which also uphold 'concepts::user_device' in order of device_manager type declaration */
        void login() { login_inplace_resolver(std::in_place_type<user_device_types>); }
        
        /* logout to all 'concepts::user_device ... Ts' in order of call-site */
        template <concepts::user_device ... Ts> requires (traits::any_same_v<Ts, Ds ... > and ... )
        void logout() { (internal::device_manager_base<Ts>::logout_devices(), ...); }

        /* logout to all 'concepts::device ... Ds' which also uphold 'concepts::user_device' in order of device_manager type declaration */
        void logout() { logout_inplace_resolver(std::in_place_type<user_device_types>); }
    // endregion
    
    protected:
        /* unpacks in_place_type of std::tuple back to a variadic args call */
        template <concepts::user_device ... Ts>
        void login_inplace_resolver(std::in_place_type_t<std::tuple<Ts...>>) { // NOLINT(readability-named-parameter)
            login<Ts ... >();
        }
        template <concepts::user_device ... Ts>
        void logout_inplace_resolver(std::in_place_type_t<std::tuple<Ts...>>) { // NOLINT(readability-named-parameter)
            logout<Ts ... >();
        }

    };
}  // namespace vaatv

#endif //VAATV_DEVICE_MANAGER_H
