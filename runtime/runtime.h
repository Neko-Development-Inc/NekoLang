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

    NekoOp& getImpl(short);

};
} // runtime

#endif //RUNTIME_H