#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#include "../common/opcodes.h"
#include "../utils/utils.h"

using namespace opcodes;

namespace compiler {
class Compiler {

private:
    Opcodes& opcodes;

public:
    explicit Compiler(Opcodes& opcodes) :
        opcodes(reinterpret_cast<Opcodes &>(opcodes)) { }

    void test();

};
} // compiler

#endif //COMPILER_H