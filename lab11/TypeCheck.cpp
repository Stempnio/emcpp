#pragma once

#include <type_traits>

template <typename T>
class hasSize {
    typedef char yesType;

    struct noType {
        char x[2];
    };

    template <typename C>
    static yesType test( decltype(&C::size) ) ;

    template <typename C>
    static noType test(...);

public:
    enum {
        value = sizeof(test<T>(0)) == sizeof(char)
    };
};

template <typename T>
inline constexpr bool hasSize_v = hasSize<T>::value;


template <typename... Ts>
using void_t = void;

template<typename T, typename = void>
struct hasValueType
        : std::false_type {};

template<typename T>
struct hasValueType<T, void_t<typename T::value_type>>
        : std::true_type {};

template <typename T>
inline constexpr bool hasValueType_v = hasValueType<T>::value;