#pragma once
#ifndef RUNTIME_H
#define RUNTIME_H

#include "../common/opcodes.h"
#include "../utils/utils.h"

namespace runtime {
class Runtime {

private:
    int abc1, abc2, abc3;

public:
    Runtime() {
        abc1 = abc2 = abc3 = 0;
    }
    ~Runtime() {
        abc1 = abc2 = abc3 = 0;
    };

    int test1();
    int test2();
    int test3();

};
} // runtime

#endif //RUNTIME_H