#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using namespace std;

inline void println(const string& str) {
    cout << str << '\n';
}

inline void println(int i) {
    cout << i << '\n';
}

template<typename Base, typename T>
inline bool instanceof(const T*) {
    return std::is_base_of<Base, T>::value;
}

#endif //UTILS_H