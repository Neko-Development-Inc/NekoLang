#pragma once

#ifndef NEKO_FUNCTION_H
#define NEKO_FUNCTION_H

#include "../../headers.h"
#include "../../runtime/ops/NekoOp.h"
#include "../../runtime/runtime.h"
#include "NekoStack.h"

class vm::NekoFunction {

public:
    const string name;
    NekoBox& owner;
    Opcodes& ops;
    vector<unique_ptr<NekoOp>> instructions;
    map<string, long long> labels;

    explicit NekoFunction(const string& name, NekoBox& owner, Opcodes& ops)
        : name(name),
          owner(owner),
          ops(ops) { }

    void init(Runtime&);

    void execute(Runtime&);

    void addInsn(unique_ptr<NekoOp>&&);

    void addLabel(unique_ptr<NekoOp>&&);

};

#endif //NEKO_FUNCTION_H