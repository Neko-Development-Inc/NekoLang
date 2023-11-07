#pragma once
#ifndef RUNTIME_H
#define RUNTIME_H

#include "../common/opcodes.h"
#include "../utils/utils.h"

using namespace opcodes;

namespace runtime {
class Runtime {

private:
    Opcodes& ops;

public:
    explicit Runtime(Opcodes& ops) :
            ops(reinterpret_cast<Opcodes &>(ops)) { }

    void test();
    void testPrint();

};
} // runtime

#endif //RUNTIME_H