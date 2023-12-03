#pragma once

#ifndef RUNTIME_H
#define RUNTIME_H

#include "../headers.h"

#include "ops/NekoOp.h"
#include "ops/NekoOpNop.cpp"
#include "ops/NekoOpReturn.cpp"

namespace runtime {
    class Runtime {

    private:
        Opcodes& ops;
        map<short, unique_ptr<NekoOp>> impls;

    public:
        explicit Runtime(Opcodes& ops) : ops(ops) { }

        void init();

        template <typename T, typename... Args>
        void addArg(unique_ptr<NekoOp>& a, T&& first, Args&&... rest) {
            a->addArg(first);
            if constexpr (sizeof...(rest) > 0)
                addArg(a, std::forward<Args>(rest)...);
        }

        template <typename T, typename... Args>
        unique_ptr<NekoOp> createImplT(short op, T&& first, Args&&... rest) {
            auto a = impls[ops[op]]->clone();
            addArg(a, first, rest...);
            return std::move(a);
        }

    };
} // runtime

#endif //RUNTIME_H