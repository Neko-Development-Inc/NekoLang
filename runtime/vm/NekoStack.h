#pragma once
#ifndef NEKO_STACK_H
#define NEKO_STACK_H

#include <mutex>

#include <any>
#include <stack>
#include <string>
#include <variant>

#include "../types/NekoObject.h"
#include "../types/NekoNumber.h"

using std::stack, std::string;

struct result {
    bool success;
    std::any* obj;
    types::NekoNumber* number;
    string* str;
    types::ObjectType type;
};

namespace vm {
class NekoStack {

private:
    stack<types::ObjectType> stackTypes;
    stack<std::any> stack;
    std::mutex _mutex;

public:
    void add(const std::any&, types::ObjectType type);
    constexpr bool has();
    int count();
    result pop();
    void process();

    types::NekoNumber* popNumber();
    string* popString();

};
}

#endif //NEKO_STACK_H