#pragma once

#ifndef UTILS_H
#define UTILS_H

#include "headers.h"
#include "runtime/types/NekoString.h"
#include "runtime/types/NekoNumber.h"
#include "runtime/types/NekoBool.h"

#define SP15 std::setprecision(15)

inline void flushOut() {
    std::cout << std::flush;
}
inline void flushErr() {
    std::cerr << std::flush;
}

template<typename T, typename... Arg>
inline void _print(std::ostream& s, T&& first, Arg&&... rest) {
    using TT = std::decay_t<T>;
    if constexpr (std::is_same<TT, bool>::value)
        s << (first ? "true" : "false");
    else if constexpr (std::is_arithmetic<TT>::value)
        s << SP15 << first;
    else if constexpr (std::is_same<TT, NekoString>::value  || std::is_same<TT, NekoNumber>::value  || std::is_same<TT, NekoBool>::value  ||
                       std::is_same<TT, NekoString*>::value || std::is_same<TT, NekoNumber*>::value || std::is_same<TT, NekoBool*>::value ||
                       std::is_same<TT, NekoString&>::value || std::is_same<TT, NekoNumber&>::value || std::is_same<TT, NekoBool&>::value)
        s << first.get();
    else if constexpr (std::is_same<TT, NekoString**>::value || std::is_same<TT, NekoNumber**>::value || std::is_same<TT, NekoBool**>::value) {
        if (first == nullptr)
            s << "<nullptr>";
        else
            s << (**first).get();
    } else if constexpr (std::is_same<TT, string>::value ||
                         std::is_same<TT, const char *>::value ||
                         std::is_convertible<TT, string>::value ||
                         std::is_convertible<TT, const char *>::value)
        s << first;
    else
        s << "{UnknownType:" << typeid(T).name() << "}";
    if constexpr (sizeof...(rest) > 0)
        _print(s, std::forward<Arg>(rest)...);
}
template<typename T, typename... Arg>
inline void _println(std::ostream& s, T&& first, Arg&&... rest) {
    _print(s, std::forward<T>(first), std::forward<Arg>(rest)..., '\n');
}

template<typename T, typename... Arg>
inline void print(T&& first, Arg&&... rest) {
    _print(std::cout, std::forward<T>(first), std::forward<Arg>(rest)...);
}
template<typename T, typename... Arg>
inline void println(T&& first, Arg&&... rest) {
    _print(std::cout, std::forward<T>(first), std::forward<Arg>(rest)..., '\n');
}

template<typename T, typename... Arg>
inline void error(T&& first, Arg&&... rest) {
    _print(std::cerr, std::forward<T>(first), std::forward<Arg>(rest)...);
}
template<typename T, typename... Arg>
inline void errorln(T&& first, Arg&&... rest) {
    _print(std::cerr, std::forward<T>(first), std::forward<Arg>(rest)..., '\n');
}

class Timer {
public:
    Timer() : Timer("NoName") { }
    Timer(const string& name) :
        name(name),
        start_time(std::chrono::high_resolution_clock::now()) { }

    ~Timer() {
        Stop();
    }

#define getCounter(time) std::chrono::time_point_cast<std::chrono::microseconds>(time).time_since_epoch().count()

    bool Stop(bool doPrint = true) {
        if (hasStopped) return false;
        hasStopped = true;
        auto end = getCounter(std::chrono::high_resolution_clock::now());
        milliseconds = (end - getCounter(start_time)) * 0.001;
        if (doPrint)
            print();
        return true;
    }

    void print() {
        println("[", name, "] Time taken: ", milliseconds, "ms");
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
        milliseconds = 0;
        hasStopped = false;
    }

    long double ms() {
        return milliseconds;
    }

private:
    string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    long double milliseconds;
    bool hasStopped = false;
};

#endif //UTILS_H