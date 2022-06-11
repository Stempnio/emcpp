#pragma once

#include <type_traits>

// void_t alias defined only for types
// that do not produce SFINAE error in its parameters
template <typename... Ts>
using void_t = void;

// Primary template
template<typename T, typename = void>
struct hasValueType
        : std::false_type {};

// Partial specialization (only for types with value_type member type)
template<typename T>
struct hasValueType<T, void_t<typename T::value_type>>
        : std::true_type {};

template <typename T>
inline constexpr bool hasValueType_v = hasValueType<T>::value;

// Primary template
template<typename T, typename = void>
struct hasSize
        : std::false_type {};

// Partial specialization (only for types with size function)
template<typename T>
struct hasSize<T, void_t<decltype(std::declval<T>().size())>>
        : std::true_type {};

template <typename T>
inline constexpr bool hasSize_v = hasSize<T>::value;