#pragma once
#ifndef NEKO_STACK_H
#define NEKO_STACK_H

#include <mutex>

#include <any>
#include <stack>
#include <string>
#include <variant>
#include <memory>

#include "../types/NekoObject.h"
#include "../types/NekoNumber.h"
#include "../types/NekoString.h"

using std::stack, std::string;

namespace vm {

struct Result {
    bool success;
    std::unique_ptr<types::NekoBase> obj;
    types::ObjectType type;
};

class NekoStack {

private:
    stack<types::ObjectType> stackTypes;
    stack<std::unique_ptr<types::NekoBase>> stack;
    std::mutex _mutex;

public:
    void add(std::unique_ptr<types::NekoBase>, types::ObjectType type);
    constexpr bool has();
    int count();
    Result pop();
    void process();

    std::unique_ptr<long double> popNumber();
    std::unique_ptr<string> popString();

};
}

#endif //NEKO_STACK_H