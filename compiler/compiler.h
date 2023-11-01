#pragma once
#ifndef COMPILER_H
#define COMPILER_H

#include "../common/opcodes.h"
#include "../utils/utils.h"

namespace compiler {
class Compiler {

private:
    int abc1, abc2, abc3;

public:
    Compiler() {
        abc1 = abc2 = abc3 = 0;
    }
    ~Compiler() {
        abc1 = abc2 = abc3 = 0;
    };

    int test1();
    int test2();
    int test3();

};
} // compiler

#endif //COMPILER_H