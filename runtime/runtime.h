#pragma once
#ifndef RUNTIME_H
#define RUNTIME_H

namespace runtime {
    class Runtime;
}

namespace ops {
    class NekoOp;
    class NekoOpNop;
    class NekoOpReturn;
}

namespace vm {
    class NekoClass;
    class NekoFunction;
}

namespace types {
    class NekoNumber;
}

#include "../common/opcodes.h"
#include "../utils/utils.h"

#include "types/NekoObject.h"
#include "types/NekoNumber.h"
#include "types/NekoString.h"

#include "ops/NekoOp.h"
#include "ops/NekoOpNop.cpp"
#include "ops/NekoOpReturn.cpp"

#include "vm/NekoClass.h"
#include "vm/NekoFunction.h"
#include "vm/NekoStack.h"

using namespace opcodes;
using ops::NekoOp;

namespace runtime {
class Runtime {

private:
    Opcodes& ops;
    map<short, unique_ptr<NekoOp>> impls;

public:
    explicit Runtime(Opcodes& ops) : ops(ops) { }

    void init();

    NekoOp& getImpl(short index);

};
} // runtime

#endif //RUNTIME_H