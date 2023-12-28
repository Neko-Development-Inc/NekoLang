#pragma once

#ifndef RUNTIME_H
#define RUNTIME_H

#include "../headers.h"

#include "ops/NekoOp.h"
#include "ops/NekoOpCs.cpp"
#include "ops/NekoOpNop.cpp"
#include "ops/NekoOpOut.cpp"
#include "ops/NekoOpPop.cpp"
#include "ops/NekoOpDup.cpp"
#include "ops/NekoOpNumber.cpp"
#include "ops/NekoOpString.cpp"
#include "ops/NekoOpConcat.cpp"
#include "ops/NekoOpReturn.cpp"

class runtime::Runtime {

private:
    Opcodes& ops;
    map<short, unique_ptr<NekoOp>> impls;

public:
    explicit Runtime(Opcodes& ops) : ops(ops) { }

    void init();

    template <typename T, typename... Args>
    void addArg(unique_ptr<NekoOp>& a, T&& first, Args&&... rest) {
        if constexpr (std::is_arithmetic<std::decay_t<T>>::value)
            a->addArg(static_cast<long double>(first));
        else
            a->addArg(first);
        if constexpr (sizeof...(rest) > 0)
            addArg(a, std::forward<Args>(rest)...);
    }

    template <typename T, typename... Args>
    unique_ptr<NekoOp> createImplT(short op, T&& first, Args&&... rest) {
        auto a = impls[ops[op]]->clone();
        addArg(a, first, rest...);
        return a;
    }

    unique_ptr<NekoOp> createImplT(short op) {
        return impls[ops[op]]->clone();
    }

};

#endif //RUNTIME_H