#pragma once
#ifndef NEKO_OP_NOP_H
#define NEKO_OP_NOP_H

#include "NekoOp.h"

#include "../runtime.h"

class NekoOpNop : NekoOp {

public:
    NekoOpNop() { }

    void execute(runtime::Runtime r) override {
        // Do nothing
        r.testPrint();
    }

};

#endif //NEKO_OP_NOP_H