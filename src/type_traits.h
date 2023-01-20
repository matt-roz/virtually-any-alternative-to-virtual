#ifndef VAATV_TYPE_TRAITS_H
#define VAATV_TYPE_TRAITS_H

#include "concepts.h"
#include <type_traits>

namespace vaatv::traits {

    // region logical traits
    template <class T, class ... Ts>
    struct all_same { constexpr static auto value = std::conjunction_v<std::is_same<T, Ts> ... >; };

    template <class T, class ... Ts>
    constexpr static auto all_same_v = all_same<T, Ts ... >::value;

    template <class T, class ... Ts>
    struct any_same { constexpr static auto value = std::disjunction_v<std::is_same<T, Ts> ... >; };

    template <class T, class ... Ts>
    constexpr static auto any_same_v = any_same<T, Ts ...>::value;
    // endregion

    // region device traits
    template <class T>
    struct is_device { constexpr static auto value = concepts::device<T>; };

    template <class T>
    constexpr static auto is_device_v = is_device<T>::value;

    template <class T>
    struct is_user_device { constexpr static auto value = concepts::user_device<T>; };

    template <class T>
    constexpr static auto is_user_device_v = is_user_device<T>::value;
    // endregion

    // region meta template traits
    namespace internal {
        template <typename, template <typename> class>
        struct tuple_filter;

        template <class ... Ts, template <class> class predicate>
        struct tuple_filter<std::tuple<Ts...>, predicate>
        {
            /* ToDo(m.rozanski): refactor
             * brew a pot of coffee and contemplate how to implement are more readable and understandable version. Until
             * then I beg the mighty compiler gods to never fail here ... ¯\_(ツ)_/¯ */
            using type =
                decltype(
                    std::tuple_cat(
                        std::declval<
                            std::conditional_t<
                                predicate<Ts>::value,
                                std::tuple<Ts>,
                                std::tuple<>
                            > // std::conditional_t
                        >() // std::declval
                    ... ) // std::tuple_cat
                ); // decltype
        }; // tuple_filter
    }  // namespace internal

    template <class tuple_t, template <class> class predicate>
    using tuple_filter_t = typename internal::tuple_filter<tuple_t, predicate>::type;
    // endregion

}  // namespace vaatv::traits

#endif //VAATV_TYPE_TRAITS_H
