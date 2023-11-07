#pragma once
#ifndef NEKO_OP_H
#define NEKO_OP_H

#include "../runtime.h"
using namespace runtime;

class NekoOp {
    virtual void execute(Runtime) = 0;
};

#endif //NEKO_OP_H