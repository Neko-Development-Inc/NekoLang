#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#include "../common/opcodes.h"
#include "../utils/utils.h"

using namespace opcodes;

namespace compiler {
class Compiler {

private:
    Opcodes& ops;

public:
    explicit Compiler(Opcodes& ops) :
            ops(reinterpret_cast<Opcodes &>(ops)) { }

    void test();

};
} // compiler

#endif //COMPILER_H