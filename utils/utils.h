#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "../runtime/types/NekoNumber.h"

using namespace std;

template <typename T> struct is_neko_number : std::false_type {};
template <> struct is_neko_number<types::NekoNumber> : std::true_type {};

template <typename T, typename... Args>
inline void println(T&& first, Args&&... rest) {
    if constexpr (std::is_same_v<T, bool>)
        cout << (first ? "true" : "false");
    else if constexpr (is_neko_number<std::remove_reference_t<T>>::value) {
        types::NekoNumber num = first;
        if (num.hasDecimals())
            cout << num.get();
        else
            cout << static_cast<long long>(num.get());
    }
    else
        cout << first;
    if constexpr (sizeof...(rest) > 0)
        println(std::forward<Args>(rest)...);
    else
        cout << '\n';
}

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

#endif //UTILS_H