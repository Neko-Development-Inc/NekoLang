#pragma once

#ifndef NEKO_CLASS_H
#define NEKO_CLASS_H

#include "../../headers.h"
#include "NekoFunction.h"

namespace vm {
class NekoClass {

public:
    string name;
    map<string, const NekoFunction*> functions;

    explicit NekoClass(string name) :
        name(std::move(name)) { }

    void addFunction(const NekoFunction&);

    void removeFunction(const string&);

};
}

#endif //NEKO_CLASS_H