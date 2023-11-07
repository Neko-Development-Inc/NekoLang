#pragma once
#ifndef NEKO_FUNCTION_H
#define NEKO_FUNCTION_H

#include <any>
#include <string>
#include <vector>
#include <utility>
#include <variant>

using std::string, std::vector, std::any;

namespace runtime {
    class Runtime;
}

namespace vm {
    class NekoClass;
}

namespace vm {
class NekoFunction {

public:
    string name;
    vector<any> instructions;
    NekoClass &owner;

    explicit NekoFunction(string name, NekoClass& owner) :
        name(std::move(name)), owner(owner) { }

    void init();

    void execute(const runtime::Runtime&);

};
}

#endif //NEKO_FUNCTION_H