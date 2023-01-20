#ifndef VAATV_CONCEPTS_H
#define VAATV_CONCEPTS_H

#include <concepts>

namespace vaatv::concepts {

    namespace internal {
        template <class T>
        concept scanable = requires (T t) {
            { T::scan() } -> std::same_as<std::vector<T>>;
        };

        template <class T>
        concept updatable = requires (T t) {
            { t.update() } -> std::same_as<void>;
        };

        template <class T>
        concept authorizable = requires (T t) {
            { t.login() } -> std::same_as<bool>;
            { t.logout() } -> std::same_as<void>;
        };
    }  // namespace internal

    template <class T>
    concept device = internal::scanable<T> and internal::updatable<T>;

    template <class T>
    concept user_device = device<T> and internal::authorizable<T>;

}  // namespace vaatv::concepts

#endif //VAATV_CONCEPTS_H
