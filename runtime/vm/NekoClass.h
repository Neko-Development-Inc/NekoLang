#pragma once

#ifndef NEKO_CLASS_H
#define NEKO_CLASS_H

#include "../../headers.h"
#include "NekoFunction.h"

namespace vm {
class NekoClass {

public:
    string path, name;
    map<string, const NekoFunction*> functions;

    explicit NekoClass(const string& name) : NekoClass("", name) { }

    explicit NekoClass(const string& path, const string& name) :
        path(path),
        name(name) { }

    void addFunction(const NekoFunction&);

    void removeFunction(const string&);

};
}

#endif //NEKO_CLASS_H