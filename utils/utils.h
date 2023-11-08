#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using namespace std;

inline void println(auto a) {
    cout << a << '\n';
}

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

#endif //UTILS_H