#pragma once
#ifndef NEKO_FUNCTION_H
#define NEKO_FUNCTION_H

#include <any>
#include <string>
#include <vector>
#include <utility>
#include <variant>

#include "../../common/opcodes.h"

using std::string, std::vector, std::any;

namespace runtime {
    class Runtime;
}

namespace vm {
    class NekoClass;
}

namespace ops {
    class NekoOp;
}

namespace opcodes {
    class Opcodes;
}

using opcodes::Opcodes,
      runtime::Runtime,
      ops::NekoOp;

namespace vm {
class NekoFunction {

public:
    string name;
    vector<NekoOp*> instructions;
    NekoClass &owner;
    Opcodes &ops;

    explicit NekoFunction(string name, NekoClass& owner, Opcodes& ops) :
        name(std::move(name)),
        owner(owner),
        ops(ops) { }

    void init(Runtime);

    void execute(const Runtime&);

};
}

#endif //NEKO_FUNCTION_H