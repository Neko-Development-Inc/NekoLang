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

#endif //UTILS_H