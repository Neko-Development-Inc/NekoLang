#pragma once

#ifndef NEKO_FUNCTION_H
#define NEKO_FUNCTION_H

#include "../../headers.h"
#include "../../common/opcodes.h"
#include "../ops/NekoOp.h"
#include "../runtime.h"
#include "NekoStack.h"

namespace vm {
class NekoFunction {

public:
    const string name;
    vector<unique_ptr<NekoOp>> instructions;
    NekoClass &owner;
    Opcodes &ops;

    explicit NekoFunction(string name, NekoClass& owner, Opcodes& ops) :
        name(std::move(name)),
        owner(owner),
        ops(ops) { }

    void init(Runtime&);

    void execute(Runtime&);

};
}

#endif //NEKO_FUNCTION_H