#pragma once
#ifndef RUNTIME_H
#define RUNTIME_H

#include "../common/opcodes.h"
#include "../utils/utils.h"

namespace runtime {
class Runtime {

private:
    opcodes::Opcodes& opcodes;

public:
    explicit Runtime(opcodes::Opcodes& opcodes) :
    opcodes(reinterpret_cast<opcodes::Opcodes &>(opcodes)) { }

    void test();

};
} // runtime

#endif //RUNTIME_H