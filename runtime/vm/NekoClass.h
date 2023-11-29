#pragma once

#ifndef NEKO_CLASS_H
#define NEKO_CLASS_H

#include "../../headers.h"
#include "NekoFunction.h"

namespace vm {
class NekoClass {

public:
    string name;
    map<string, NekoFunction> functions{};

    explicit NekoClass(string name) :
        name(std::move(name)) { }

    void addFunction(const NekoFunction& func);

    void removeFunction(const string& s);

};
}

#endif //NEKO_CLASS_H