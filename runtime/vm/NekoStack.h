#pragma once

#ifndef NEKO_STACK_H
#define NEKO_STACK_H

#include "../../headers.h"

#include "../types/NekoObject.h"
#include "../types/NekoNumber.h"
#include "../types/NekoString.h"

namespace vm {

struct Result {
    bool success;
    std::unique_ptr<NekoBase> obj;
    ObjectType type;
};

class NekoStack {

private:
    stack<ObjectType> stackTypes;
    stack<std::unique_ptr<NekoBase>> _stack;
    std::mutex _mutex;

public:
    void add(std::unique_ptr<NekoBase>, ObjectType);
    bool has();
    int count();
    Result pop();
    void process();

    std::unique_ptr<long double> popNumber();
    std::unique_ptr<string> popString();

};
}

#endif //NEKO_STACK_H